/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:08:48 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:09:27 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_token(char **ps, char *end_s, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < end_s && ft_strchr(SPACE, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (*s)
		s = switch_token(s, end_s, &ret);
	if (eq)
		*eq = s;
	while (s < end_s && ft_strchr(SPACE, *s))
		s++;
	*ps = s;
	return (ret);
}

int	search_last_quote(char *s, char *es, char mark)
{
	int	it;
	int	bow;

	it = 0;
	bow = 0;
	while (s < es && !ft_strchr(SYMBOL, *s) && !ft_strchr("<>", *s))
	{
		s++;
		if (*s == mark)
			bow = it;
		else if (*s == '\\')
			s++;
		it++;
	}
	return (bow);
}

char	*redir_tok(char *s, char *es, int *ret)
{
	if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			*ret = '+';
			s++;
		}
	}
	else if (*s == '<')
	{
		s++;
		if (*s == '<')
		{
			*ret = 'H';
			s++;
		}
	}
	return (s);
}

char	*quotes(char *s, char *es, int *ret)
{
	int	i;

	i = 0;
	if (*s == '\'' || *s == '\"')
	{
		*ret = *s;
		i = search_last_quote(s, es, *s);
		s++;
		while (*s && !ft_strchr(SYMBOL, *s) && i-- >= 0)
			s++;
	}
	return (s);
}

char	*switch_token(char *s, char *es, int *ret)
{
	if (*s)
	{
		if (ft_strchr(SYMBOL, *s))
			s++;
		else if (*s == '>' || *s == '<'
			|| *s == '\'' || *s == '\"')
		{
			s = redir_tok(s, es, ret);
			s = quotes(s, es, ret);
		}
		else
		{
			*ret = 'a';
			while (s < es && !ft_strchr(SPACE, *s)
				&& !ft_strchr("<>", *s) && !ft_strchr(SYMBOL, *s))
				s++;
		}
	}
	return (s);
}
