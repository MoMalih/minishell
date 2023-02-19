/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:09:38 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/19 03:17:09 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

int	count_nodes(t_envlist *env_list)
{
	int			count;
	t_envlist	*curr;

	curr = env_list;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

char	**allocate_envp(int count)
{
	char	**envp;

	envp = malloc(sizeof(char *) * (count + 1));
	if (envp == NULL)
	{
		return (NULL);
	}
	return (envp);
}

void	create_env_var(char **envp, t_envlist *curr, int i)
{
	int	name_len;
	int	content_len;
	int	len;
	int	j;

	j = 0;
	content_len = ft_strlen(curr->content);
	name_len = ft_strlen(curr->name);
	len = name_len + content_len + 2;
	envp[i] = malloc(sizeof(char) * len);
	if (envp[i] == NULL)
	{
		while (j < i)
		{
			free(envp[j]);
			j++;
		}
		free(envp);
		return ;
	}
	ft_strcpy(envp[i], curr->name);
	envp[i][name_len] = '=';
	ft_strcpy(envp[i] + name_len + 1, curr->content);
}

char	**env_var(t_envlist *env_list)
{
	int			count;
	char		**envp;
	t_envlist	*curr;
	int			i;

	envp = allocate_envp(count);
	count = count_nodes(env_list);
	if (envp == NULL)
		return (NULL);
	curr = env_list;
	i = 0;
	while (curr)
	{
		create_env_var(envp, curr, i);
		i++;
		curr = curr->next;
	}
	envp[count] = NULL;
	return (envp);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
