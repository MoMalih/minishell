/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 04:37:12 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/17 04:53:05 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

int	export_builtin(char **args, t_envlist *env)
{
	int			i;
	char		**tmp;
	int			ret;
	t_envlist	*temp;

	ret = EXIT_SUCCESS;
	i = 1;
	temp = env;
	if (!args[i])
	{
		while (temp->next != NULL)
		{
			printf("%s=%s\n", temp->name, temp->content);
			temp = temp->next;
		}
		printf("%s=%s\n", temp->name, temp->content);
		return (ret);
	}
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			printf("export: %s: not a valid identifier\n", args[i]);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(args[i]);
            set_env_var(&env, tmp[0], tmp[1]);
            free_str_tab(tmp);
        }
        i++;
    }
    return (ret);
}

void    free_str_tab(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int set_env_var(t_envlist **env, char *key, char *value)
{
    t_envlist   *temp;
    t_envlist   *prev;

    temp = *env;
    prev = *env;
    while (temp != NULL)
    {
        if (strcmp(temp->name, key) == 0)
        {
            free(temp->content);
            temp->content = ft_strdup(value);
            return (0);
        }
        prev = temp;
        temp = temp->next;
    }
    temp = (t_envlist*)malloc(sizeof(t_envlist));
    temp->name = ft_strdup(key);
    temp->content = ft_strdup(value);
    temp->next = NULL;
    if (*env == NULL)
    {
        *env = temp;
        return (0);
    }
    prev->next = temp;
    return (0);
}

/*int set_env_var(t_envlist *env, char *key, char *value)
{
    t_envlist   temp;
    t_envlist   prev;

    temp = env;
    prev = env;
    while (temp->next != NULL)
    {
        if (ft_strcmp(temp->name, key) == 0)
        {
            free(temp->content);
            temp->content = ft_strdup(value);
            return (0);
        }
        prev = temp;
        temp = temp->next;
    }
    if (ft_strcmp(temp->name, key) == 0)
    {
        free(temp->content);
        temp->content = ft_strdup(value);
        return (0);
    }
    temp->next = malloc(sizeof(t_envlist));
    temp->next->name = ft_strdup(key);
    temp->next->content = ft_strdup(value);
    temp->next->next = NULL;
    return (0);
}*/

 char   **get_key_value_pair(char *str)
{
    char    **ret;
    int     i;
    int     j;

    ret = malloc(sizeof(char *) * 3);
    ret[0] = malloc(sizeof(char) * (ft_strlen(str) + 1));
    ret[1] = malloc(sizeof(char) * (ft_strlen(str) + 1));
    ret[2] = NULL;
    i = 0;
    j = 0;
    while (str[i] != '=')
    {
        ret[0][i] = str[i];
        i++;
    }
    ret[0][i] = '\0';
    i++;
    while (str[i])
    {
        ret[1][j] = str[i];
        i++;
        j++;
    }
    ret[1][j] = '\0';
    return (ret);
}

int is_valid_env_var_key(char *str)
{
    int i;

    i = 0;
    if (ft_isdigit(str[i]))
        return (0);
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}
