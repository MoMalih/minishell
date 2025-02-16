/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:17:52 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/19 21:19:42 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    MINISHELL_H
# define  MINISHELL_H

// #include "execution/sshell.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

// define  

# define MAX_ARG 10
# define SPACE " \t\v\r\n"
# define SYMBOL "|()&;"
# define EXEC_ID 1
# define REDIR_ID 2
# define PIPE_ID 3
# define LIST_ID 4
# define BACK_ID 5
// structs

typedef enum s_bool{
	false,
	true,
}	t_bool;

typedef struct s_envlist
{
	struct s_envlist	*prev;
	char				*name;
	char				*content;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_quote
{
	int	single_count;
	int	double_count;
	int	flag;
}	t_quote;

typedef struct s_cmd
{
	int	id;
}	t_cmd;

typedef struct s_exec_c
{
	int		id;
	char	*args[MAX_ARG];
	char	*end_args[MAX_ARG];
	t_bool	expand[MAX_ARG];
}	t_exec_c;

typedef struct s_redir_c
{
	int		id;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	t_bool	expand;
	int		flag;
	int		fd;
}	t_redir_c;

typedef struct s_pipe_c
{
	int		id;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe_c;

typedef struct s_list_c
{
	int		id;
	t_cmd	*left;
	t_cmd	*right;
}	t_list_c;

typedef struct s_back_c
{
	int		id;
	t_cmd	*cmd;
}	t_back_c;

typedef struct s_env{
	t_envlist	*envlist;
	char		**env_var;
	char		*cwd;
	int			ac;
	char		**av;
	t_cmd		*cmd;
	char		*line;
	int			cmd_count;
	int			exit;
}	t_env;

// Prototypes

// env_tools
void		update_shell(t_env *env);
t_envlist	*init_env_node(char *str);
void		to_list(char **arr, t_envlist **env_node);
void		init_env(t_env *env, int ac, char **av, char **env_var);

// helper
int			fork_protected(void);
void		*ft_memset(void *b, int c, size_t len);
void		terminated(char *s);
char		*ft_strchr(const char *s, int c);
char		**strstrip(char *str, char c);
void		safe_free(void **ptr);

//  parse
t_cmd		*parsecmd(char *buf, t_envlist *env_list);
t_cmd		*parseline(char **ptr, char *end_ptr);
t_cmd		*parsepipe(char **ptr, char *end_ptr);
t_cmd		*parseexec(char **ptr, char *end_ptr, char **cmd, char **end_cmd);
t_cmd		*parseredirs(t_cmd *cmd, char **ptr, char *end_ptr);
t_cmd		*parseblock(char **ptr, char *end_ptr);

// constructors
t_cmd		*exec_c(void);
t_cmd		*new_cmd(char **args, char *redir, char *file, struct s_cmd *next);
void		free_cmd(t_cmd *cmd);
t_cmd		*redir_c(t_cmd *sub_cmd, char *file, char *efile, int flag);
t_cmd		*pipe_c(t_cmd *left, t_cmd *right);
t_cmd		*list_c(t_cmd *left, t_cmd *right);
t_cmd		*back_c(t_cmd *backcmd);

// term
t_cmd		*exec(t_cmd *cmd);
t_cmd		*redir(t_cmd *cmd);
t_cmd		*pip(t_cmd *cmd);
t_cmd		*back(t_cmd *cmd);
t_cmd		*list(t_cmd *cmd);

// token

int			init_token(char **ptr, char *end_ptr, char **cmd, char **end_cmd);
char		*switch_token(char *s, char *es, int *ret);
int			jump(char **ptr, char *end_ptr, char *mark);
t_cmd		*n_term(t_cmd *cmd);
void		my_printf(int fd, const char *s, ...);
void		print_cmd(t_cmd *cmd);
// signal

void		handle_int(int signo);
void		handle_quit(int sig_code);
// void	rl_replace_line (const char *text, int clear_undo);

// printf
void		my_printf(int fd, const char *fmt, ...);
void		quotes_handler(t_cmd *cmd, t_envlist *env);
void		count_quotes(char cmd_char, int *single_count, int *double_count);
int			parse_quotes(char *input);
char		*here_doc(char *input, char *command);
int			set_fd(int flag);
// void    runcmd(t_cmd *cmd, t_envlist *env);

// QUOTE
char		*inner_quotes(char *s, char **var, int s_len, int *dubl);
int			is_alpha_num(int c);
char		*find_env(char *name, t_envlist *list);
char		*replace_str(char *str, char *orig, char *rep);
int			check_unclosed(char *arg);
char		*delete_q(char *str, int len, int *sing, int *dubl);
int			validate(char *cmd, int *single_count, int *double_count, int flag);
char		*delete_quotes(char *cmd, int *single_count, int *double_count);
char		*trim_quotes(const char *s, size_t len);

#endif
