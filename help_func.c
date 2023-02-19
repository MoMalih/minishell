/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:08:08 by zbidouli          #+#    #+#             */
/*   Updated: 2023/02/19 20:08:26 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*x;

	x = (char *)b;
	i = 0;
	while (i < len)
	{
		x[i] = (char)c;
		i++;
	}
	return (b);
}

void	terminated(char *s)
{
	if (s)
	{
		printf("%s\n", s);
		kill(0, SIGTERM);
	}
	exit(1);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i > -1)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}

char	**strstrip(char *str, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	arr = malloc(sizeof(char *) * 2);
	arr[0] = malloc(sizeof(char) * (len + 1));
	arr[0][len] = 0;
	if (str[len])
		arr[1] = malloc(sizeof(char) * (ft_strlen(str) - len));
	else
		arr[1] = NULL;
	j = -1;
	i = 0;
	while (str[++j])
	{
		if (!i && (str[j] == c))
			i++;
		arr[i][j - len * i] = str[j + i];
	}
	return (arr);
}

void	safe_free(void **ptr)
{
	if (*ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}
