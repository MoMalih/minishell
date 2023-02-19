/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 00:28:41 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/19 00:28:44 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

void	exec_cmd(t_exec_c *ecmd, t_envlist *env)
{
	char	*path;

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

void	exec_builtins(char **args, t_envlist *env)
{
	if (ft_strcmp(args[0], "echo") == 0)
		echo_builtin(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		cd_builtin(args, &env);
	else if (ft_strcmp(args[0], "pwd") == 0)
		pwd_builtin();
	else if (ft_strcmp(args[0], "export") == 0)
		export_builtin(args, env);
	else if (ft_strcmp(args[0], "unset") == 0)
		unset_builtin(args, &env);
	else if (ft_strcmp(args[0], "env") == 0)
		env_builtin(env, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit_builtin(args, env);
	else
		panic("unknown builtins");
}

bool	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v');
}

int	is_valid_env_var_key(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	free_str_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
