#pragma once

#ifdef __MAIN__
#define __EXTERN1(type,name) type name
#define __EXTERN2(type,name,value) type name = value
#else
#define __EXTERN1(type,name) extern type name
#define __EXTERN2(type,name,value) extern type name
#endif
__EXTERN1(struct wrt_radauth_config,config);
