/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:22:21 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:06:48 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parsepipe(char **ptr, char *end_ptr)
{
	t_cmd	*commd;
	char	*cmd;
	char	*end_cmd;

	commd = parseexec(ptr, end_ptr, &cmd, &end_cmd);
	if (jump(ptr, end_ptr, "|"))
	{
		init_token(ptr, end_ptr, 0, 0);
		commd = pipe_c(commd, parsepipe(ptr, end_ptr));
	}
	return (commd);
}

t_cmd	*parseline(char **ptr, char *end_ptr)
{
	t_cmd	*cmd;

	cmd = parsepipe(ptr, end_ptr);
	while (jump(ptr, end_ptr, "&"))
	{
		init_token(ptr, end_ptr, 0, 0);
		cmd = back_c(cmd);
	}
	if (jump(ptr, end_ptr, ";"))
	{
		init_token(ptr, end_ptr, 0, 0);
		cmd = list_c(cmd, parseline(ptr, end_ptr));
	}
	return (cmd);
}

t_cmd	*parsecmd(char *buf, t_envlist *envlist)
{
	t_cmd	*cmd;
	char	*e_ptr;

	e_ptr = buf + strlen(buf);
	cmd = parseline(&buf, e_ptr);
	jump(&buf, e_ptr, " ");
	if (buf != e_ptr)
	{
		printf("l_ovrs: [%s]\n", buf);
		terminated("syntax\n");
	}
	n_term(cmd);
	quotes_handler(cmd, envlist);
	return (cmd);
}

	// print_cmd(cmd);