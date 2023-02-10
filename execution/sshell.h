#ifndef SSHELL_H
#define SSHELL_H

// #ifndef MINISHELL_H
// #define MINISHELL_H

#include "../minishell.h"
#include <stdbool.h>
#include <sys/stat.h>

#define PATH_MAX 4096

void    runcmd(t_cmd *cmd, t_envlist *env);
int     fork1(void);
char    *search_env_var(t_envlist *env, char *str);
char    *path_finder(char *key, t_envlist *lenv);
void    *memcpy1(void *dst, const void *src, size_t n);
char	*strjoin1(char const *s1, char const *s2);
size_t	strlen1(const char *s);
char    **env_var(t_envlist *environment);
char	**split1(char const *str, char c);
int     pwd_bi();
int     echo_bi(char **args);
void    panic(char *mssg);


#endif 
