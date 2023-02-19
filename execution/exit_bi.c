/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 00:03:38 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/16 00:08:31 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

int	exit_builtin(char **args, t_envlist *env)
{
	int		exit_code;
	bool	error;

	error = false;
	if (!args || !args[1])
		exit_code = 0;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			exit(1);
		}
		else if (args[2])
		{
			printf("exit: too many arguments\n");
			exit(1);
		}
	}
	kill(0, SIGTERM);
	exit(exit_code);
	return (0);
}

int	get_exit_code(char *arg, bool *error)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			*error = true;
			return (0);
		}
		exit_code = exit_code * 10 + (arg[i] - '0');
		i++;
	}
	return (exit_code);
}
