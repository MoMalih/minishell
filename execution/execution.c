/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 05:11:33 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/19 00:24:26 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

void	handle_redir_cmd(t_redir_c *rcmd, t_envlist *env)
{
	close(rcmd->fd);
	if (rcmd->flag == 72)
	{
		runcmd(rcmd->cmd, env);
	}
	if (open(rcmd->file, rcmd->flag) < 0)
	{
		panic("open failed");
		exit(1);
	}
	runcmd(rcmd->cmd, env);
}

void	handle_list_cmd(t_list_c *lcmd, t_envlist *env)
{
	if (fork1() == 0)
		runcmd(lcmd->left, env);
	wait(0);
	runcmd(lcmd->right, env);
}

void	handle_pipe_cmd(t_pipe_c *pcmd, t_envlist *env)
{
	int	p[2];

	if (pipe(p) < 0)
		panic("pipe");
	if (fork1() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left, env);
	}
	if (fork1() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right, env);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}

void	handle_back_cmd(t_back_c *bcmd, t_envlist *env)
{
	if (fork1() == 0)
		runcmd(bcmd->cmd, env);
}

void	runcmd(t_cmd *cmd, t_envlist *env)
{
	if (cmd == 0)
	{
		panic("cmd == 0");
		exit(1);
	}
	if (cmd->id == EXEC_ID)
		exec_cmd((t_exec_c *)cmd, env);
	else if (cmd->id == REDIR_ID)
		handle_redir_cmd((t_redir_c *)cmd, env);
	else if (cmd->id == LIST_ID)
		handle_list_cmd((t_list_c *)cmd, env);
	else if (cmd->id == PIPE_ID)
		handle_pipe_cmd((t_pipe_c *)cmd, env);
	else if (cmd->id == BACK_ID)
		handle_back_cmd((t_back_c *)cmd, env);
	else
	{
		panic("unknown runcmd");
		exit(1);
	}
}
