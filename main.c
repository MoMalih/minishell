/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:13:15 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:25:11 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/sshell.h"

int	jump(char **ptr, char *end_ptr, char *mark)
{
	char	*tmp;

	tmp = *ptr;
	while (tmp < end_ptr && ft_strchr(SPACE, *tmp))
		tmp++;
	*ptr = tmp;
	return (*tmp && ft_strchr(mark, *tmp));
}

t_cmd	*n_term(t_cmd *cmd)
{
	if (cmd == 0)
		return (0);
	if (cmd)
	{
		if (cmd->id == EXEC_ID)
			cmd = exec(cmd);
		else if (cmd->id == PIPE_ID)
			cmd = pip(cmd);
		else if (cmd->id == LIST_ID)
			cmd = list(cmd);
		else if (cmd->id == BACK_ID)
			cmd = back(cmd);
		else if (cmd->id == REDIR_ID)
			cmd = redir(cmd);
	}
	return (cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*buf;
	int		fd;
	int		s;
	t_env	env_inf;
	t_cmd	*cmd;

	init_env(&env_inf, ac, av, env);
	signal(SIGINT, handle_int);
	signal(SIGQUIT, handle_quit);
	buf = readline("$> ");
	while (buf)
	{
		add_history(buf);
		if (fork_protected() == 0)
		{
			cmd = parsecmd(buf, env_inf.envlist);
			runcmd(cmd, env_inf.envlist);
		}
		else
			wait(NULL);
	buf = readline("$> ");
	}
	kill(0, SIGTERM);
	exit(1);
}
