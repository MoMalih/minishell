/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 05:11:33 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/15 05:40:58 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

void	panic(char *s)
{
	ft_putstr_fd(s, 2);
	exit(1);
}

int	is_buitin(char *cmd)
{
	if (strcmp(cmd, "echo") == 0)
		return (1);
	else if (strcmp(cmd, "cd") == 0)
		return (1);
	else if (strcmp(cmd, "pwd") == 0)
		return (1);
	else if (strcmp(cmd, "export") == 0)
		return (1);
	else if (strcmp(cmd, "unset") == 0)
		return (1);
	else if (strcmp(cmd, "env") == 0)
		return (1);
	else if (strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

void	exec_builtins(char **args, t_envlist *env)
{
	if (strcmp(args[0], "echo") == 0)
		echo_builtin(args);
	else if (strcmp(args[0], "cd") == 0)
		cd_builtin(args, env);
	else if (strcmp(args[0], "pwd") == 0)
		pwd_builtin();
	else if (strcmp(args[0], "export") == 0)
		export_builtin(args, env);
	else if (strcmp(args[0], "unset") == 0)
		unset_builtin(args, &env);
	else if (strcmp(args[0], "env") == 0)
		env_builtin(env, args);
	else if (strcmp(args[0], "exit") == 0)
		exit_builtin(args, env);
	else
		panic("unknown builtins");
}

void	runcmd(t_cmd *cmd, t_envlist *env)
{
	int			p[2];
	t_back_c	*bcmd;
	t_exec_c	*ecmd;
	t_list_c	*lcmd;
	t_pipe_c	*pcmd;
	t_redir_c	*rcmd;
	char		*path;

	if (cmd == 0)
	{
		panic("cmd == 0");
		exit(1);
	}
	if (cmd->id == EXEC_ID)
	{
		ecmd = (t_exec_c *)cmd;
		if (ecmd->args[0] == 0)
			exit(1);
		if (is_buitin(ecmd->args[0]))
		{
			exec_builtins(ecmd->args, env);
			exit(0);
		}
		else
		{
			path = path_finder(ecmd->args[0], env);
			execve(path, ecmd->args, env_var(env));
			panic("exec failed");
		}
	}
	else if (cmd->id == REDIR_ID)
	{
		rcmd = (t_redir_c *)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->flag) < 0)
		{
			panic("open failed");
			exit(1);
		}
		runcmd(rcmd->cmd, env);
	}
	else if (cmd->id == LIST_ID)
	{
		lcmd = (t_list_c *)cmd;
		if (fork1() == 0)
			runcmd(lcmd->left, env);
		wait(0);
		runcmd(lcmd->right, env);
	}
	else if (cmd->id == PIPE_ID)
	{
		pcmd = (t_pipe_c *)cmd;
		if (pipe(p) < 0)
			panic("pipe");
		if (fork1() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left, env);
		}
		if (fork1() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right, env);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
	}
	else if (cmd->id == BACK_ID)
	{
		bcmd = (t_back_c *)cmd;
		if (fork1() == 0)
			runcmd(bcmd->cmd, env);
	}
	else
		panic("unknown runcmd");
	exit(0);
}

char	*search_env_var(t_envlist *env, char *str)
{
	int	i;
	int	l;

	i = 0;
	l = strlen(str);
	while (env)
	{
		if (strcmp(env->name, str) == 0)
			return (env->content);
		env = env->next;
	}
	printf("env not found");
	return (NULL);
}

char	*path_finder(char *key, t_envlist *lenv)
{
	char			*path;
	char			**paths;
	struct stat		buf;
	int				i;

	i = 0;
	key = strjoin1("/", key);
	path = search_env_var(lenv, "PATH");
	paths = split1(path, ':');
	while (paths[i])
	{
		if (!stat(strjoin1(paths[i], key), &buf))
			return (strjoin1(paths[i], key));
		i++;
	}
	printf("path not found\n");
	return (NULL);
}
