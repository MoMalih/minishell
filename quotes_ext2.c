/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_ext2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:12:22 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:17:55 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*inner_quotes(char *s, char **var, int s_len, int *dubl)
{
	char	*new_s;
	char	*tmp_s;
	size_t	v_len;

	new_s = ft_strnstr(s, *var, s_len) - 1;
	tmp_s = s;
	v_len = ft_strlen(*var) - 1;
	if (s && var && v_len && new_s)
	{
		if ((*new_s == '\"') && (new_s[v_len + 2] == '\"'))
		{
			s = replace_str(s, (new_s + 1), "\0");
			new_s = ft_strjoin(trim_quotes(new_s, (v_len + 3)),
					&new_s[v_len + 3]);
			*dubl -= 1;
			s = ft_strjoin(s, new_s);
		}
		else if ((*new_s == '\'') && (new_s[v_len + 2] == '\''))
		{
			*var = ft_strjoin("'", *var);
			*var = ft_strjoin(*var, "'");
		}
		return (s);
	}
	return (ft_strdup(s));
}
				// printf(">>1S :: [%s]\n\n", s);

char	*delete_q(char *str, int len, int *sing, int *dubl)
{
	while ((str[0] == '\'' || str[0] == '\"')
		&& len > 2 && (*sing > 0 || *dubl > 0))
	{
		if (str[0] == '\'' && str[(len - 1)] == '\'')
		{
			*sing -= 1;
			str = trim_quotes(str, len);
			len = ft_strlen(str);
		}
		else if (str[0] == '\"' && str[(len - 1)] == '\"')
		{
			*dubl -= 1;
			str = trim_quotes(str, len);
			len = ft_strlen(str);
		}
	}
	return (str);
}

	char	*delete_quotes(char *cmd, int *single_count, int *double_count)
{
	if (check_unclosed(cmd) && (*single_count > 0 || *double_count > 0))
	{
		cmd = delete_q(cmd, ft_strlen(cmd), single_count, double_count);
		return (cmd);
	}
	return (cmd);
}
