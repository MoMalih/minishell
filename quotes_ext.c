/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_ext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:10:52 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:15:02 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_quotes(char arg, int *doublequote, int *singlequote)
{
	if (arg == '\"' || arg == '\'')
	{
		if (arg == '\"' && *doublequote == 0)
			*doublequote += 1;
		else if (arg == '\"' && *doublequote == 1)
			*doublequote -= 1;
	}
	else if (arg == '\'' && *singlequote == 0)
		*singlequote += 1;
	else if (arg == '\'' && *singlequote == 1)
		*singlequote -= 1;
}

int	check_unclosed(char *arg)
{
	int	singlequote;
	int	doublequote;
	int	it;

	singlequote = 0;
	doublequote = 0;
	it = 0;
	while (arg[it])
	{
		switch_quotes(arg[it], &doublequote, &singlequote);
		it++;
	}
	if (doublequote == 0 || singlequote == 0)
		return (1);
	terminated("UNCLOSED_QUOTES");
	return (0);
}

int	parse_quotes(char *input)
{
	int	len;

	len = ft_strlen(input);
	if (input[0] == '\'' || input[0] == '\"')
	{
		if (input[0] == '\'' && input[len - 1] == '\'')
			return (1);
		else if (input[0] == '\"' && input[len - 1] == '\"')
			return (1);
		else
			return (0);
	}
	return (1);
}

int	is_alpha_num(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c == '_' || c == '-'))
		return (1);
	return (0);
}

void	count_quotes(char cmd, int *single_count, int *double_count)
{
	if (cmd)
	{
		if (cmd == '\'')
			*single_count += 1;
		else if (cmd == '\"')
			*double_count += 1;
	}
}
