#ifndef CFG_LIB_H
#define CFG_LIB_H

//#include "apps.h"

void	cfg_free();
int	cfg_load(char *filename);
int	cfg_save(char *filename);
char	*cfg_get(char *key);
int	cfg_set(char *key, char *data);
char	*cfg_table_get(char *key, int idx);

int	keyremap(char *ucikey, char* key);
#endif
