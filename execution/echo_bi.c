/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:59:40 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/15 23:04:01 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

static bool	nn_flag(char *arg)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	if (arg[i] != '-')
		return (n_flag);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		n_flag = true;
	return (n_flag);
}

int	echo_builtin(char **args)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 1;
	while (args[i] && nn_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
