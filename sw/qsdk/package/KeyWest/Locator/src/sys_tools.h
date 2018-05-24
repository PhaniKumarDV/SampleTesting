#ifndef SYS_TOOLS_H
#define SYS_TOOLS_H

int get_IfHWAddr(char *interface, uint8_t *addr);
int get_IfIPAddr(char *interface, uint32_t *ipaddr);
int get_IfNetMask(char *interface, uint32_t *mask);
char *get_lanIf();
char *get_sysVersion();

#endif
