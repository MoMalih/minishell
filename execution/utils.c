/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:09:38 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/16 00:02:18 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

void	*memcpy1(void *dst, const void *src, size_t n)
{
	size_t	sn;

	sn = n;
	if (!dst && !src)
		return (NULL);
	if (src == dst)
		return (dst);
	while (n--)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (dst - sn);
}

char	*strjoin1(char const *s1, char const *s2)
{
	char	*ret;
	size_t	sumlen;

	if (!s1)
		return (NULL);
	sumlen = strlen1(s1) + strlen1(s2);
	ret = malloc(sizeof(char) * (sumlen + 1));
	if (!ret)
		return (NULL);
	memcpy1(ret, s1, strlen1(s1));
	memcpy1(ret + strlen1(s1), s2, strlen1(s2));
	ret[sumlen] = 0;
	return (ret);
}

size_t	strlen1(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

/*char    **env_var(t_envlist *environment)
{
    char **env;
    t_envlist *tmp;
    int i;
	int len;

    tmp = environment;
    while (tmp)
    {
        tmp = tmp->next;
        len++;
    }
    env = (char **)malloc(sizeof(char*) * (len + 1));
	if (env == NULL)
	{
		panic("env_var failled");
		exit(1);
	}
    i = 0;
    while (environment)
    {
        env[i] = environment->name;
        environment = environment->next;
        i++;
    }
    env[i] = NULL;
    return (env);
}*/

char	**env_var(t_envlist *env_list)
{
	t_envlist	*curr;
    char		**envp;
	int			count;
    int			i;

	count = 0;
	curr = env_list;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (envp == NULL)
		return (NULL);
	curr = env_list;
	i = 0;
	while (curr)
	{
		int name_len = strlen(curr->name);/**/
        int content_len = strlen(curr->content);/**/
        int len = name_len + content_len + 2;
        envp[i] = malloc(sizeof(char) * len);
        if (envp[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(envp[j]);
            free(envp);
            return NULL;
        }
        strcpy(envp[i], curr->name);/*11*/
        envp[i][name_len] = '=';
        strcpy(envp[i] + name_len + 1, curr->content);/**/
        i++;
        curr = curr->next;
    }
    envp[count] = NULL;

    return envp;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
