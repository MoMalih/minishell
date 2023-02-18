/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:00:03 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/18 00:24:25 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rl_replace_line(const char *text,int clear_undo)
{
	int			len;

	len = strlen(text);
	strcpy(rl_line_buffer, text);
	rl_end = len;
}

void	handle_int(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_quit(int sig_code)
{
	if (sig_code == SIGQUIT)
	{
		rl_redisplay();
	}
}
