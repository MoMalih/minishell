/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:04:10 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/15 23:09:30 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

int	env_builtin(t_envlist *env, char **args)
{
	t_envlist	temp;

	temp = *env;
	if (args && args[1])
	{
		printf("too many arguments\n");
		return (2);
	}
	if (!env)
	{
		panic("env: env is empty");
		return (EXIT_FAILURE);
	}
	while (temp.next != NULL)
	{
		printf("%s = %s\n", temp.name, temp.content);
		temp = *(temp.next);
	}
	if (env)
		printf("%s = %s\n", temp.name, temp.content);
	return (EXIT_SUCCESS);
}
