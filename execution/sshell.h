/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 01:24:31 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/16 01:25:35 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SSHELL_H
# define	SSHELL_H

#include "../minishell.h"
#include <stdbool.h>
#include <sys/stat.h>

#define PATH_MAX    1024

int		fork1(void);
void	panic(char *s);
int		is_buitin(char *cmd);
void	exec_builtins(char **args, t_envlist *env);
void	runcmd(t_cmd *cmd, t_envlist *env);
char	*search_env_var(t_envlist *env, char *str);
char	*path_finder(char *key, t_envlist *lenv);
char	**split1(char const *str, char c);
void	*memcpy1(void *dst, const void *src, size_t n);
char	*strjoin1(char const *s1, char const *s2);
size_t	strlen1(const char *s);
char	**env_var(t_envlist *env_list);
bool	    cd_builtin(char **args, t_envlist **env);
//int     cd_builtin(char **args);
int		echo_builtin(char **args);
int		env_builtin(t_envlist *env, char **args);
int		exit_builtin(char **args, t_envlist *env);
int		get_exit_code(char *arg, bool *error);
void	pwd_builtin();
t_envlist	*create_env_node(char *key, char *value);
int		unset_builtin(char **args, t_envlist **env);
int		is_valid_env_var_key(char *str);
char	**get_key_value_pair(char *str);
int		set_env_var(t_envlist **env, char *key, char *value);
void	free_str_tab(char **str);
int		ft_strcmp(char *s1, char *s2);
int     export_builtin(char **args, t_envlist *env);
char	*get_env_var_value(t_envlist *env, char *var);
void	free_ptr(void *ptr);
void    set_env_var_cd(t_envlist **env, char *name, char *value);
bool ft_isspace(int c);
char	*ft_strdup1(const char *s1);

# endif 
