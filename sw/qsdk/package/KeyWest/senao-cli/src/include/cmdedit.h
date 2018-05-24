#ifndef CMDEDIT_H
#define CMDEDIT_H
#define MAX_LINELEN 255
int     cmdedit_read_input(char* promptStr, char* command);

#ifdef CONFIG_ASH
extern const char *cmdedit_path_lookup;
#endif

#ifdef CONFIG_FEATURE_COMMAND_SAVEHISTORY
void    load_history ( const char *fromfile );
void    save_history ( const char *tofile );
#endif

#if CONFIG_FEATURE_COMMAND_EDITING_VI
void	setvimode ( int viflag );
#endif

int get_terminal_width_height(int fd, int *width, int *height);
ssize_t safe_read(int fd, void *buf, size_t count);

#endif /* CMDEDIT_H */
