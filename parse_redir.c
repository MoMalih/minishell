/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:06:21 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:06:40 by zbidouli         ###   ########.fr       */
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