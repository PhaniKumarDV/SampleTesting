#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>
#include "locator.h"

//#define DEBUG_set
//#define DEBUG_get

#define FREE(_p) (_p? free(_p), _p = NULL: NULL)
#define GET 1
#define GETVALUE 2


typedef struct entry
{
	char *key;
	char *data;
	struct entry *sub;
	struct entry *next;
} entry, *pentry;

static pentry pehead = NULL;
static pentry pe = NULL;

static pentry cfg_find(char *key, pentry *e)
{
	pentry returnVal = NULL;
	
	return returnVal;
}


void cfg_free()
{

}

int cfg_load(char *filename)
{
	int returnVal = 1;
	
	return returnVal;
}

int cfg_save(char *filename)
{
	int returnVal=system("uci commit");
	
	return returnVal;
}

int keyremap(char *method,char *ucikey, char *key, char *value){
	
	if(strcmp(key,"state_network.lan.ifname") == 0){
		if(method == GET){
			sprintf(ucikey,"%s","uci -P /var/state get network.lan.ifname");
		}else if(method == GETVALUE){
			//value[strlen(value) - 1]='\0'; //remove the new line
		}
	}else
	if(strcmp(key,"WLANOpMode") == 0){
		if(method == GET){
			sprintf(ucikey,"%s","uci get wireless.@wifi-iface[1].mode");
		}else if(method == GETVALUE){
			     if(strncmp(value,"ap\n"     ,10) == 0){sprintf(value,"%s\n","0" );}
			else if(strncmp(value,"apwds\n"  ,10) == 0){sprintf(value,"%s\n","6" );}
			else if(strncmp(value,"sta\n"    ,10) == 0){sprintf(value,"%s\n","1" );}
			else if(strncmp(value,"stawds\n" ,10) == 0){sprintf(value,"%s\n","7" );}
			else if(strncmp(value,"br\n"     ,10) == 0){sprintf(value,"%s\n","2" );}
			else if(strncmp(value,"rp\n"     ,10) == 0){sprintf(value,"%s\n","3" );}
			else if(strncmp(value,"apr\n"    ,10) == 0){sprintf(value,"%s\n","4" );}
			else if(strncmp(value,"cr\n"     ,10) == 0){sprintf(value,"%s\n","5" );}
			else if(strncmp(value,"sifyob\n" ,10) == 0){sprintf(value,"%s\n","8" );}
			else if(strncmp(value,"sifyos\n" ,10) == 0){sprintf(value,"%s\n","9" );}

			else if(strncmp(value,"ap'\n"     ,10) == 0){sprintf(value,"%s\n","0" );}
			else if(strncmp(value,"apwds'\n"  ,10) == 0){sprintf(value,"%s\n","6" );}
			else if(strncmp(value,"sta'\n"    ,10) == 0){sprintf(value,"%s\n","1" );}
			else if(strncmp(value,"stawds'\n" ,10) == 0){sprintf(value,"%s\n","7" );}
			else if(strncmp(value,"br'\n"     ,10) == 0){sprintf(value,"%s\n","2" );}
			else if(strncmp(value,"rp'\n"     ,10) == 0){sprintf(value,"%s\n","3" );}
			else if(strncmp(value,"apr'\n"    ,10) == 0){sprintf(value,"%s\n","4" );}
			else if(strncmp(value,"cr'\n"     ,10) == 0){sprintf(value,"%s\n","5" );}
			else if(strncmp(value,"sifyob'\n" ,10) == 0){sprintf(value,"%s\n","8" );}
			else if(strncmp(value,"sifyos'\n" ,10) == 0){sprintf(value,"%s\n","9" );}
			else {
				//fprintf(stderr,"%s:opmode not define:%s\n",__func__,value);
				return 2;
			}
		}
	}else
	if(strcmp(key,"SystemName") == 0){
		if(method == GET){
			sprintf(ucikey,"%s","uci get system.@system[0].hostname");
		}else if(method == GETVALUE){
			// do nothing, pass
		}
	}else
	if(strcmp(key,"LANDHCPC") == 0){
		if(method == GET){
			sprintf(ucikey,"%s","uci get network.lan.proto");
		}else if(method == GETVALUE){
			if(strncmp(value,"dhcp\n"     ,10) == 0){sprintf(value,"%s\n","1" );}
			else{sprintf(value,"%s\n","0" );}
		}
	}else
	if(strcmp(key,"LANGatewayIP") == 0){
		if(method == GET){
			sprintf(ucikey,"%s","uci get network.lan.gateway");
		}else if(method == GETVALUE){
			// do nothing, pass
		}
	}else
	if(strcmp(key,"UserName") == 0){
		if(method == GET){
			sprintf(ucikey,"%s",". /lib/auth.sh;get_username");
			//sprintf(ucikey,"%s","echo asdf");
		}else if(method == GETVALUE){
			// do nothing, pass
		}
	}else
	if(strcmp(key,"SysPassword") == 0){
		if(method == GET){
			sprintf(ucikey,"%s","grep \"/:\" /etc/httpd.conf|cut -d \":\" -f 3");
			//sprintf(ucikey,"%s","echo asdf");
		}else if(method == GETVALUE){
			// do nothing, pass
		}
	}else
	{
		fprintf(stderr,"%s %s: not define:%s\n",__func__,__FUNCTION__,key);	
		return 1;
	}


return 0;
}


char *cfg_get(char *key)
{
	#ifdef DEBUG
	log(LOG_LOG, "%s: start\n", __FUNCTION__);
	#endif
	//pentry tmp = cfg_find(key, NULL);
	//char *data = tmp != NULL? (tmp->sub == NULL? tmp->data: tmp->sub->data): NULL;
	char data[100];
	char ucikey[100];
	char cmd[150];
	FILE *fpipe;
	int ret;
	memset(data, 0, sizeof(data));	

	ret=keyremap(GET,ucikey,key,"");
	if(ret != 0) {
		#ifdef DEBUG
		log(LOG_LOG, "%s: key remap error\n", __FUNCTION__);
		#endif
		fputs("key remap error\n",stderr);exit(2);
	}
	int n=sprintf(cmd,"%s",ucikey);
	#ifdef DEBUG
	log(LOG_LOG, "%s: popen-start:%s\n", __FUNCTION__,cmd);
	#endif
	fpipe = (FILE *)popen(cmd, "r");
	#ifdef DEBUG
	log(LOG_LOG, "%s: popen-fpipe-%s\n", __FUNCTION__,cmd);
	#endif

	if(! (fpipe) )
	{
		log(LOG_LOG, "%s: pipe error\n", __FUNCTION__);
		//perror("pipe error");
	}
	#ifdef DEBUG
	log(LOG_LOG, "%s: popen-2\n", __FUNCTION__);
	#endif

	fread(data,sizeof(char),sizeof(data),fpipe);
	pclose(fpipe);

	#ifdef DEBUG_get
	log(LOG_LOG, "%s: data:%s,len:%d ucikey:%s\n", __FUNCTION__,data,strlen(data),ucikey);
	#endif
	ret=keyremap(GETVALUE,ucikey, key, data);

	char *eol=strchr(data,'\n');
	if( eol != NULL) {
		//log(LOG_LOG, "%s: strchr\n", __FUNCTION__);
		//fprintf(stderr,"%x,%x\n",eol,eol-data);		
		data[eol-data]='\0'; 
	}

	#ifdef DEBUG
	log(LOG_LOG, "%s: data2:%s,len:%d ucikey:%s\n", __FUNCTION__,data,strlen(data),ucikey);
	#endif
	return data != NULL? strcpy(malloc(strlen(data) + 1), data): NULL;
}

int cfg_set(char *key, char *data)
{
	#ifdef DEBUG_set
	log(LOG_LOG, "%s: key:%s,data:%s\n", __FUNCTION__,key,data);
	#endif
	
	FILE *fpipe;
	int ret;
	char cmd[150];
	int n=sprintf(cmd,"uci set %s=%s",key,data);
	#ifdef DEBUG_set
	log(LOG_LOG, "%s: popen-start:%s\n", __FUNCTION__,cmd);
	#endif
	fpipe = (FILE *)popen(cmd, "r");
	#ifdef DEBUG_set
	log(LOG_LOG, "%s: popen-fpipe-%s\n", __FUNCTION__,cmd);
	#endif	
	if(! (fpipe) )
	{
		log(LOG_LOG, "%s: pipe error\n", __FUNCTION__);
	}
	#ifdef DEBUG_set
	log(LOG_LOG, "%s: popen-2\n", __FUNCTION__);
	#endif

	fread(data,sizeof(char),sizeof(data),fpipe);
	pclose(fpipe);	
	return 0;
}

char *cfg_table_get(char *key, int idx)
{
	pentry tmp = cfg_find(key, NULL);
	
	if(tmp != NULL && tmp->sub != NULL)
		for(tmp = tmp->sub; idx-- > 0 && tmp != NULL; tmp = tmp->next);
	
	return tmp != NULL? strcpy(malloc(strlen(tmp->data) + 1), tmp->data): NULL;
}

