/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:22:21 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/17 21:37:31 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseredirs(t_cmd *o_cmd, char **ptr, char *end_ptr)
{
	int			tok;
	char		*cmd;
	char		*end_cmd;
	t_exec_c	*exec_c;

	while (jump(ptr, end_ptr, "<>"))
	{
		tok = init_token(ptr, end_ptr, 0, 0);
		if (init_token(ptr, end_ptr, &cmd, &end_cmd))
		{
			if (tok == '<' && tok)
			{
				o_cmd = redir_c(o_cmd, cmd, end_cmd, O_RDONLY, 0);
				break ;
			}
			else if (tok == '>' && tok)
			{
				o_cmd = redir_c(o_cmd, cmd, end_cmd, O_WRONLY | O_CREAT, 1);
				break ;
			}
			else if (tok == '+' && tok)
			{
				o_cmd = redir_c(o_cmd, cmd, end_cmd, O_APPEND | O_CREAT, 1);
				break ;
			}
			else if (tok == 'H' && tok)
			{
				o_cmd = redir_c(o_cmd, cmd, end_cmd, 'H', -1);
				exec_c = (t_exec_c *)o_cmd;
				here_doc(exec_c->args, cmd);
				break ;
			}
		}
		else
			terminated("missing file for redirection");
	}
	return (o_cmd);
}

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

t_cmd	*parseexec(char **ptr, char *end_ptr)
{
	char		*cmd;
	char		*end_cmd;
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
		tok = init_token(ptr, end_ptr, &cmd, &end_cmd);
		if (tok == 0)
			break ;
		// else if(tok != 'a')
		// 	terminated("syntax");
		e_cmd->args[ac] = cmd;
		e_cmd->end_args[ac] = end_cmd;
		ac++;
		if (ac >= MAX_ARG)
			terminated("too many args");
		res = parseredirs(res, ptr, end_ptr);
	}
	e_cmd->args[ac] = 0;
	e_cmd->end_args[ac] = 0;
	return (res);
}

t_cmd	*parsepipe(char **ptr, char *end_ptr)
{
	t_cmd	*cmd;

	cmd = parseexec(ptr, end_ptr);
	if (jump(ptr, end_ptr, "|"))
	{
		init_token(ptr, end_ptr, 0, 0);
		cmd = pipe_c(cmd, parsepipe(ptr, end_ptr));
	}
	return (cmd);
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
