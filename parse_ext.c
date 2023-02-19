/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:04:34 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:18:23 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseblock(char **ptr, char *end_ptr)
{
	t_cmd	*cmd;

	if (!jump(ptr, end_ptr, "("))
		terminated("parseblock");
	init_token(ptr, end_ptr, 0, 0);
	cmd = parseline(ptr, end_ptr);
	if (!jump(ptr, end_ptr, ")"))
		terminated("syntax - missing )");
	init_token(ptr, end_ptr, 0, 0);
	cmd = parseredirs(cmd, ptr, end_ptr);
	return (cmd);
}
void	init_cmd(t_exec_c	*e_cmd, char *cmd, char *end_cmd, int *ac)
{
	e_cmd->args[*ac] = cmd;
	e_cmd->end_args[*ac] = end_cmd;
	*ac += 1;
	if (*ac >= MAX_ARG)
		terminated("too many args");
}
	// printf("AC>>>> {%d}", *ac);

t_cmd	*parseexec(char **ptr, char *end_ptr, char **cmd, char **end_cmd)
{
	int			tok;
	int			ac;
	t_exec_c	*e_cmd;
	t_cmd		*res;

	if (jump(ptr, end_ptr, "("))
		return (parseblock(ptr, end_ptr));
	res = exec_c();
	e_cmd = (t_exec_c *)res;
	ac = 0;
	res = parseredirs(res, ptr, end_ptr);
	while (!jump(ptr, end_ptr, "|)&;"))
	{
		tok = init_token(ptr, end_ptr, &(*cmd), &(*end_cmd));
		if (tok == 0)
			break ;
		else if (!tok)
			terminated("SYNTAX");
		init_cmd(e_cmd, *cmd, *end_cmd, &ac);
		res = parseredirs(res, ptr, end_ptr);
	}
	init_cmd(e_cmd, 0, 0, &ac);
	return (res);
}
