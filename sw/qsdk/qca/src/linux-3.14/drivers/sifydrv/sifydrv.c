/*
 * devone.c
 *
 * Update: 2007/12/19 Yutaka Hirata
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/poll.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <linux/gpio.h>
#include <linux/ioctl.h>

#define SIFY_MAGIC					'k'
#define GET_NMEA_READ_PERIOD 		_IOR(SIFY_MAGIC,0,int)
#define GET_LOW_POWER_STATE 		_IOR(SIFY_MAGIC,1,int)
#define SET_LOW_POWER_TIMER_VAL 	_IOR(SIFY_MAGIC,2,int)

#define MAJOR_NUM			0
#define MINOR_NUM			0
#define DEV_NO				1
#define PPS_GPIO_NO			5
#define DGSAP_GPIO_NO		63

MODULE_LICENSE("Dual BSD/GPL");

static struct cdev devsify_cdev;  
static struct class *devone_class = NULL;
static dev_t devone_dev;

// 1pps irq no from GPIO5
unsigned int n1pps_irq_no = 0;
// dying gasp irq no from GPIO 63
unsigned int ndgasp_irq_no = 0; 

// the result of dying gasp
static volatile unsigned int nlost_power_flg = 0;
// the total number of 1pps 
static volatile unsigned int nNMEA_read_period = 0;

// timer to compute the dying gasp time for 20ms
struct timer_list Timer_Dgasp;
unsigned int nTimerValue = 0;

// timeout function for timer 
static void Dgasp_timeout(unsigned long arg){
	printk("%s , %d ms achievement from received dying gasp IRQ \n",__func__,(nTimerValue*1000/HZ));
}

// IRQ handler for 1pps when GPIO5 pull high
static irqreturn_t pps_irq(int irq, void *dev_id)
{
    //printk("1pps irq %d received \n", irq);
	nNMEA_read_period++;
	
    return IRQ_RETVAL(1);
}

// IRQ handler for dying gasp when GPIO63 pull low
static irqreturn_t lost_pwr_irq(int irq, void *dev_id)
{
    printk("Dying gasp irq %d received \n", irq);
    nlost_power_flg = 1;
		
	if(nTimerValue > 0)
		mod_timer(&Timer_Dgasp, jiffies + nTimerValue);
	
    return IRQ_RETVAL(1);
}

ssize_t devsify_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	return -EFAULT;
}


ssize_t devsify_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	int retval;

	return (retval);
}

static long devsify_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	//printk("ioctl, cmd=0x%02x, arg=0x%02lx\n",cmd, arg);

	switch (cmd) {
	case GET_NMEA_READ_PERIOD:
	    copy_to_user((unsigned int *)arg,&nNMEA_read_period,sizeof(nNMEA_read_period));
		printk("GET_NMEA_READ_PERIOD ret =%d \n",*((unsigned int *)arg));
		break;
	case GET_LOW_POWER_STATE:	    
		 copy_to_user((unsigned int *)arg,&nlost_power_flg,sizeof(nlost_power_flg));
		//printk("GET_LOW_POWER_STATE ret =%d \n",*((unsigned int *)arg));
	    break;
	case SET_LOW_POWER_TIMER_VAL:
		copy_from_user(&nTimerValue,(unsigned int *)arg,sizeof(nTimerValue));
		printk("set dgasp timer value = %d ms \n",nTimerValue);
		nTimerValue = (nTimerValue*HZ/1000);
		printk("jiffies delta = %d \n",nTimerValue);		
		break;
	default:
		return -1;
	}
	return 0;
}
int devsify_close(struct inode *inode, struct file *filp)
{
	return 0;   /* success */
}

int devsify_open(struct inode *inode, struct file *filp)
{
	return 0;   /* success */
}

struct file_operations devone_fops = {
	.owner = THIS_MODULE,
	.open = devsify_open,
	.release = devsify_close,
	.read = devsify_read,
	.write = devsify_write,
	.unlocked_ioctl	= devsify_ioctl,
};

// setup the requested input direction GPIO and return the IRQ no.
static int GPIO_IRQ_Setup(char* cDevName,unsigned int GPIO_NO)
{
	int nIRQ_Num = -1;
	
	if(gpio_request(GPIO_NO,cDevName) < 0)
	{
		printk("%s gpio %d failed to requested \n",cDevName,GPIO_NO);
		return nIRQ_Num;
	}
	
	if(gpio_direction_input(GPIO_NO) < 0)
	{
		printk("failed to set gpio %d as input \n",GPIO_NO);
		return nIRQ_Num;
	}
	
	nIRQ_Num = gpio_to_irq(GPIO_NO);
	printk("irq no. for %s (GPIO %d) = %d registered \n",cDevName,GPIO_NO,nIRQ_Num);
	gpio_export(GPIO_NO,0);
	
	return nIRQ_Num;	
}

static int devsify_init(void)
{
	dev_t dev;
	int nRet = 0;
	int cdev_err = 0;
	int nMajor = 0;	
		
	struct class_device *class_dev = NULL;

	dev = MKDEV(MAJOR_NUM, 0);
	nRet = alloc_chrdev_region(&dev, 0, DEV_NO, "sifydrv");
	if (nRet){
		printk("alloc chrdev region failed \n");
		goto error;
	}
	nMajor = MAJOR(dev);

	cdev_init(&devsify_cdev, &devone_fops);
	devsify_cdev.owner = THIS_MODULE;
	devsify_cdev.ops = &devone_fops;
	cdev_err = cdev_add(&devsify_cdev, MKDEV(nMajor, MINOR_NUM), 1);
	if (cdev_err){
		printk("add device failed \n");
		goto error;
	}
	/* register class */
	devone_class = class_create(THIS_MODULE, "sifydrv");
	if (IS_ERR(devone_class)) {
		printk("create class failed \n\n");
		goto error;
	}
	devone_dev = MKDEV(nMajor, MINOR_NUM);
#ifdef LINUX_3_14
	class_dev = class_device_create(
					devone_class, 
					NULL, 
					devone_dev,
					NULL, 
					"sifydrv");
#else
	class_dev = device_create(
					devone_class, 
					NULL, 
					devone_dev,
					NULL, 
					"sifydrv");
#endif
	
	// setup the GPIO5 as interrupt for 1pps
	n1pps_irq_no = GPIO_IRQ_Setup("1pps",PPS_GPIO_NO);
	
	if(n1pps_irq_no > 0)
		nRet = request_irq(n1pps_irq_no, pps_irq, IRQF_TRIGGER_RISING, "1pps", NULL);
	
    if (nRet < 0) {
        printk(KERN_ALERT "%s: 1pps request_irg failed with %d\n",__func__, nRet);
        goto error;
    }
	// setup the GPIO63 as interrupt for dying gasp
	ndgasp_irq_no = GPIO_IRQ_Setup("dgasp",DGSAP_GPIO_NO);
	
	if(ndgasp_irq_no > 0)
		nRet = request_irq(ndgasp_irq_no, lost_pwr_irq, IRQF_TRIGGER_FALLING, "dgasp", NULL);
	
    if (nRet < 0) {
        printk(KERN_ALERT "%s: request_irg failed with %d\n",
            __func__, nRet);
        goto error;
    }
	
	//initialize the timer that used to compute dying gasp survive time
	init_timer(&Timer_Dgasp);
	Timer_Dgasp.function = Dgasp_timeout;
	
	printk(KERN_ALERT "devsify driver(major %d) installed.\n", nMajor);

	return 0;

error:
	if (cdev_err == 0)
		cdev_del(&devsify_cdev);

	if (nRet == 0)
		unregister_chrdev_region(dev, DEV_NO);

	return -1;
}

static void devsify_exit(void)
{
	dev_t dev = MKDEV(MAJOR_NUM, 0);

	/* unregister class */
#ifdef LINUX_3_14	
	class_device_destroy(devone_class, devone_dev);
#else
	device_destroy(devone_class, devone_dev);	
#endif
	class_destroy(devone_class);

	cdev_del(&devsify_cdev);
	unregister_chrdev_region(dev, DEV_NO);
    free_irq(n1pps_irq_no, NULL);
    free_irq(ndgasp_irq_no, NULL);	
	
	gpio_free(PPS_GPIO_NO);
	gpio_free(DGSAP_GPIO_NO);
	
	del_timer(&Timer_Dgasp);
	printk(KERN_ALERT "devsify driver removed.\n");
}

module_init(devsify_init);
module_exit(devsify_exit);

