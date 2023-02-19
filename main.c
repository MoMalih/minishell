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

// void	 print_cmd(t_cmd *cmd)
// {
// 	int	i = -1;
// 	t_back_c *bcmd;
// 	t_exec_c *ecmd;
// 	t_list_c *lcmd;
// 	t_pipe_c *pcmd;
// 	t_redir_c *rcmd;

// 	if (cmd == 0)
// 		exit(0);

// 	switch (cmd->id)
// 	{
// 	default:
// 		terminated("printcmd\n");

// 	case EXEC_ID:
// 		// printf("<< printing >>\n");
// 		ecmd = (t_exec_c *)cmd;
// 		// if(ecmd->args[0] == 0)
// 		//   exit();
// 		// exec(ecmd->argv[0], ecmd->argv);
// 		printf("<<<< >>>EXEC \n");
// 		while (ecmd->args[i++])
// 		{
// 			printf(" EXEC ARGs [%s]\n", ecmd->args[i]);
// 			// printf(" EXPEND [%d] \n", ecmd->expand[i]);
// 			// printf("exec EXEC [%s] \n", ecmd->end_args[i]);
// 		}
// 		// fflush(0);
// 		break;

// 	case REDIR_ID:
// 		rcmd = (t_redir_c *)cmd;
// 		printf("<<<<<< R >>>>>>>>\n");
// 		printf("CMD >>>>>>>> [%d]\n", rcmd->cmd->id);
// 		printf("FILE >>>>>>>> [%s]\n", rcmd->file);
// 		// printf(" EXPEND [%d] \n", rcmd->expend);
// 		printf("FD >>>>>>>> [%d]\n", rcmd->fd);
// 		printf("Flag >>>>>>>> [%c]\n", rcmd->flag);

// 		// fflush(0);
// 		// if(fork_protected() == 0)
// 		print_cmd(rcmd->cmd);
// 		break;

// 	case LIST_ID:
// 		lcmd = (t_list_c *)cmd;
// 		printf("<<<< LIST >>\n");
// 		printf("<<left : [%d] >>", lcmd->left->id);
// 		printf("            <<right : [%d] >>\n", lcmd->right->id);
// 		// fflush(0);
// 		// if(fork_protected() == 0)
// 		// if(fork_protected() == 0)
// 		print_cmd(lcmd->left);
// 		print_cmd(lcmd->right);
// 		break;

// 	case PIPE_ID:
// 		pcmd = (t_pipe_c *)cmd;
// 		printf("<<<< P >>\n");
// 		printf("<< left : [%d] >>", pcmd->left->id);
// 		printf("            <<right : [%d] >>\n", pcmd->right->id);
// 		// fflush(stdout);
// 		// if(fork_protected() == 0)
// 		// if(fork_protec÷ted() == 0)
// 		print_cmd(pcmd->left);
// 		print_cmd(pcmd->right);
// 		break;	

// 	case BACK_ID:
// 		bcmd = (t_back_c *)cmd;
// 		printf("<<<< B >>>>\n");
// 		printf("<< back : [%d] >>\n", bcmd->cmd->id);

// 		// fflush(2);
// 		// if(fork_protected() == 0)
// 		print_cmd(bcmd->cmd);
// 		break;
// 	}
// }

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
	while ((buf = readline("$> ")) && buf)
	{
		add_history(buf);
		if (fork_protected() == 0)
		{
			cmd = parsecmd(buf, env_inf.envlist);
			runcmd(cmd, env_inf.envlist);
		}
		else
			wait(NULL);
	}
	kill(0, SIGTERM);
	exit(1);
}
