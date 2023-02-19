/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:22:21 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 01:37:17 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*handle_redir_less(t_cmd *o_cmd, char *cmd, char *end_cmd)
{
	return (redir_c(o_cmd, cmd, end_cmd, '<'));
}

t_cmd	*handle_redir_more(t_cmd *o_cmd, char *cmd, char *end_cmd)
{
	return (redir_c(o_cmd, cmd, end_cmd, '>'));
}

t_cmd	*handle_redir_more_append(t_cmd *o_cmd, char *cmd, char *end_cmd)
{
	return (redir_c(o_cmd, cmd, end_cmd, '+'));
}

t_cmd	*handle_heredoc(t_cmd *o_cmd, char *cmd, char *end_cmd)
{
	t_exec_c	*exec_c;

	o_cmd = redir_c(o_cmd, cmd, end_cmd, 'H');
	exec_c = (t_exec_c *)o_cmd;
	here_doc(exec_c->args, cmd);
	return (o_cmd);
}

t_cmd	*parseredirs(t_cmd *o_cmd, char **ptr, char *end_ptr)
{
	char	*cmd;
	char	*end_cmd;
	int		tok;

	tok = 0;
	while (jump(ptr, end_ptr, "<>"))
	{
		tok = init_token(ptr, end_ptr, 0, 0);
		if (init_token(ptr, end_ptr, &cmd, &end_cmd))
		{
			if (tok == '<' && tok)
				o_cmd = handle_redir_less(o_cmd, cmd, end_cmd);
			else if (tok == '>' && tok)
				o_cmd = handle_redir_more(o_cmd, cmd, end_cmd);
			else if (tok == '+' && tok)
				o_cmd = handle_redir_more_append(o_cmd, cmd, end_cmd);
			else if (tok == 'H' && tok)
				o_cmd = handle_heredoc(o_cmd, cmd, end_cmd);
			else
				terminated("invalid redirection operator");
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