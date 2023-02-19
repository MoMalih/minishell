/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:37:49 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:12:41 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_double_quotes(char *cmd, int *double_count)
{
	char	*var;

	while (*double_count > 0)
		cmd = inner_quotes(cmd, &var, ft_strlen(cmd), double_count);
	return (cmd);
}

char	*replace_env_var(char *cmd, int *it_e, t_envlist *list,
			t_quote *sd)
{
	int		it_s;
	int		len;
	char	*env_var;
	char	*var;

	len = 0;
	it_s = *(it_e) + 1;
	while (is_alpha_num(cmd[++(*it_e)]) && *it_e < ft_strlen(cmd))
		len++;
	env_var = ft_substr(cmd, it_s, len);
	var = find_env(env_var, list);
	if (var)
	{
		cmd = replace_str(cmd, env_var, var);
		cmd = delete_q(cmd, ft_strlen(cmd),
				&sd->single_count, &sd->double_count);
		sd->flag++;
		if (cmd && sd->double_count > 0)
			cmd = handle_double_quotes(cmd, &sd->double_count);
	}
	return (cmd);
}

char	*find_and_replace_env_var(char *cmd, t_envlist *list, t_quote *sd)
{
	int	it_e;

	it_e = 0;
	if (!parse_quotes(cmd))
		terminated("Error: Unclosed quotes\n");
	while (cmd[it_e] && it_e < ft_strlen(cmd))
	{
		count_quotes(cmd[it_e], &sd->single_count, &sd->double_count);
		if (cmd[it_e] == '$' && validate(&cmd[it_e], &sd->single_count,
				&sd->double_count, sd->flag) && check_unclosed(cmd))
		{
			cmd = replace_env_var(cmd, &it_e, list,
					sd);
		}
		it_e++;
	}
	return (cmd);
}

void	search_exp(char **cmd, t_envlist *list)
{
	int		it;
	t_quote	sd;

	it = 0;
	sd.single_count = 0;
	sd.double_count = 0;
	sd.flag = 0;
	while (cmd[it] && it < MAX_ARG)
	{
		cmd[it] = find_and_replace_env_var(cmd[it], list, &sd);
		cmd[it] = delete_quotes(cmd[it], &sd.single_count, &sd.double_count);
		it++;
	}
}

		// printf("<< SD :: [%d] [%d]\n", sd.single_count, sd.double_count);
// void	search_exp(char **cmd, t_envlist *list)
// {
// 	int		it;
// 	int		flag;
// 	int		it_e;
// 	int		it_s;
// 	int		it_v;
// 	int		single_count;
// 	int		double_count;
// 	int		len;
// 	char	*env_var;
// 	char	*var;

// 	it = 0;
// 	it_s = 0;
// 	single_count = 0;
// 	double_count = 0;
// 	flag = 0;
// 	while (cmd[it] && it < MAX_ARG)
// 	{
// 		it_e = 0;
// 		if (!parse_quotes(cmd[it]))
// 			terminated("Error: Unclosed quotes\n");
// 		while (cmd[it][it_e] && it_e < ft_strlen(cmd[it]))
// 		{
// 			var = NULL;
// 			len = 0;
// 			count_quotes(cmd[it][it_e], &single_count, &double_count);
// 			if (cmd[it][it_e] == '$' && validate(&cmd[it][it_e],
// 				&single_count, &double_count, flag)
// 				&& check_unclosed(cmd[it]))
// 			{
// 				it_s = it_e + 1;
// 				while (is_alpha_num(cmd[it][++it_e])
// 				&& it_e < ft_strlen(cmd[it]))
// 					len++;
// 				env_var = ft_substr(cmd[it], it_s, len);
// 				var = find_env(env_var, list);
// 				if (var)
// 				{
// 					cmd[it] = replace_str(&(*cmd[it]), env_var, var);
// 					cmd[it] = delete_q(&(*cmd[it]), ft_strlen(cmd[it]),
// 							&single_count, &double_count);
// 					flag++;
// 					if (cmd[it] && double_count > 0)
// 					{
// 						while (double_count > 0)
// 							cmd[it] = inner_quotes(&(*cmd[it]), &var,
// 									ft_strlen(cmd[it]), &double_count);
// 					}
// 				}
// 			}
// 			it_e++;
// 		}
// 		if (check_unclosed(cmd[it]) && (single_count > 0 || double_count > 0))
// 		{
// 			cmd[it] = delete_q(&(*cmd[it]), ft_strlen(cmd[it]),
// 					&single_count, &double_count);
// 			break ;
// 		}
// 			it++;
// 	}
// }
					// printf(">>CMD :: [%s]\n", &(*cmd[it]));
						// printf(">>VARS2 :: [%s]\n", var);
								// printf(">>CMD2 :: [%s]\n", cmd[it]);
							// printf(">>CMD :: [%s]\n", &(*cmd[it]));
				// printf(">>CMD_HEREEE*** :: [%s]\n", &(*cmd[it]));

void	quotes_handler(t_cmd *cmd, t_envlist *envlist)
{
	t_exec_c	*ecmd;
	t_list_c	*lcmd;
	t_pipe_c	*pcmd;
	t_redir_c	*rcmd;

	if (cmd == 0)
		exit(0);
	if (cmd->id == EXEC_ID)
	{
		ecmd = (t_exec_c *)cmd;
		search_exp(ecmd->args, envlist);
	}
	else if (cmd->id == REDIR_ID)
	{
		rcmd = (t_redir_c *)cmd;
	}
	else if (cmd->id == PIPE_ID)
	{
		pcmd = (t_pipe_c *)cmd;
		quotes_handler(pcmd->left, envlist);
		quotes_handler(pcmd->right, envlist);
	}
}
		// search_exp(rcmd->file, envlist);
