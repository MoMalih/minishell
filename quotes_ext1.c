/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_ext1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:11:28 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:11:37 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(char *name, t_envlist *list)
{
	t_envlist	*it_list;

	it_list = list;
	while (it_list->next && name && it_list->name)
	{
		if (ft_strlen(it_list->name) == ft_strlen(name))
		{
			if (!ft_strncmp(it_list->name, name, ft_strlen(name)))
				return (it_list->content);
		}
		it_list = it_list->next;
	}
	return (NULL);
}

int	validate(char *cmd, int *single_count, int *double_count, int flag)
{
	int	len;
	int	up;
	int	it;

	it = 0;
	while (cmd[it - 1] == '\"' || cmd[it - 1] == '\'')
		cmd --;
	len = ft_strlen(cmd);
	up = 0;
	if (cmd[0] == '\'' || cmd[len -1] == '\'')
	{
		if (flag >= 1)
			return (1);
		else if (*single_count == 1)
			return (0);
		else if (*single_count % 2 != 0)
			return (0);
	}
	return (1);
}

char	*trim_quotes(const char *s, size_t len)
{
	char	*new_s;

	if (len >= 2 && (s[0] == '\"' && s[len - 1] == '\"'))
	{
		new_s = malloc(len - 1);
		ft_strlcpy(new_s, s + 1, len - 1);
		new_s[len - 2] = '\0';
		return (new_s);
	}
	else if (len >= 2 && (s[0] == '\'' && s[len - 1] == '\''))
	{
		new_s = malloc(len - 1);
		ft_strlcpy(new_s, s + 1, len - 1);
		new_s[len - 2] = '\0';
		return (new_s);
	}
	return (strdup(s));
}

char	*replace_str(char *str, char *orig, char *rep)
{
	char	*buf;
	int		it;

	buf = ft_strnstr(str, orig, ft_strlen(str)) - 1;
	if (buf)
	{
		buf = ft_strjoin(ft_substr(str, 0, buf - str), rep);
		str = ft_strnstr(str, orig, ft_strlen(str)) + ft_strlen(orig);
		str = ft_strjoin(buf, str);
	}
	return (str);
}

void	count(char *str, int *sing, int *dubl)
{
	while (*str)
	{
		if (*str == '\'' )
			*sing += 1;
		else if (*str == '\"')
			*dubl += 1;
		str++;
	}
}
