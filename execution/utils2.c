/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 00:03:17 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/19 00:03:24 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

char	*search_env_var(t_envlist *env, char *str)
{
	int	i;
	int	l;

	i = 0;
	l = strlen(str);
	while (env)
	{
		if (ft_strcmp(env->name, str) == 0)
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
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}
