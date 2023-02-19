/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 01:24:31 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/19 12:00:38 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SSHELL_H
# define SSHELL_H

# include "../minishell.h"
# include <stdbool.h>
# include <sys/stat.h>
# define PATH_MAX 1024

int			ft_strcmp(char *s1, char *s2);
size_t		strlen1(const char *s);
void		*memcpy1(void *dst, const void *src, size_t n);
int			fork1(void);
char		*strjoin1(char const *s1, char const *s2);
char		*get_env_var_value(t_envlist *env, char *var);
bool		ft_isspace(int c);
void		set_env_var_cd(t_envlist **env, char *name, char *value);
void		update_pwd_env_var(t_envlist *env, char *oldpwd, char *newpwd);
void		change_dir(t_envlist **env, char *path);
int			cd_builtin(char **args, t_envlist **env);
int			echo_builtin(char **args);
int			env_builtin(t_envlist *env, char **args);
void		exec_cmd(t_exec_c *ecmd, t_envlist *env);
void		exec_builtins(char **args, t_envlist *env);
void		handle_redir_cmd(t_redir_c *rcmd, t_envlist *env);
void		handle_list_cmd(t_list_c *lcmd, t_envlist *env);
void		handle_pipe_cmd(t_pipe_c *pcmd, t_envlist *env);
void		handle_back_cmd(t_back_c *bcmd, t_envlist *env);
void		runcmd(t_cmd *cmd, t_envlist *env);
int			exit_builtin(char **args, t_envlist *env);
int			get_exit_code(char *arg, bool *error);
int			export_builtin(char **args, t_envlist *env);
void		free_str_tab(char **str);
int			set_env_var(t_envlist **env, char *key, char *value);
t_envlist	*create_env_node(char *key, char *value);
char		**get_key_value_pair(char *str);
int			is_valid_env_var_key(char *str);
void		pwd_builtin(void);
char		**split1(char const *str, char c);
int			unset_builtin(char **args, t_envlist **env);
t_envlist	*find_env_variable(char *name, t_envlist **env);
void		remove_env_variable(t_envlist *var, t_envlist **env);
int			count_nodes(t_envlist *env_list);
void		create_env_var(char **envp, t_envlist *curr, int i);
char		**env_var(t_envlist *env_list);
char		*search_env_var(t_envlist *env, char *str);
char		*path_finder(char *key, t_envlist *lenv);
int			is_buitin(char *cmd);
void		panic(char *s);
void		two_point(void);
char		*ft_strcpy(char *dest, char *src);
void		print_env_vars(t_envlist *env);
void		update_env_var(t_envlist *node, char *value);
void		go_to(char **path, t_envlist **env, char **args);
void		move_path(char *path, t_envlist **env);
void		go_root(void);
void		go_dash(char **path, t_envlist **env);

#endif 
