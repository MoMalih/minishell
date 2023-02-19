/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpfunc_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:07:49 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:08:28 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd(int flag)
{
	if ((flag == (O_WRONLY | O_CREAT))
		|| (flag == (O_APPEND | O_CREAT | O_WRONLY)))
		return (1);
	else if (flag == 'H')
		return (-1);
	else
		return (0);
}

int	fork_protected(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		terminated("fork");
	return (pid);
}
