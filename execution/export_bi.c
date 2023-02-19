/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 04:37:12 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/19 03:57:30 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

// Helper function to print all environment variables
void	print_env_vars(t_envlist *env)
{
	t_envlist	*temp;

	temp = env;
	while (temp->next != NULL)
	{
		printf("%s=%s\n", temp->name, temp->content);
		temp = temp->next;
	}
	printf("%s=%s\n", temp->name, temp->content);
}

int	export_builtin(char **args, t_envlist *env)
{
	int		i;
	char	**tmp;

	i = 1;
	if (!args[i])
	{
		print_env_vars(env);
		return (1);
	}
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			printf("export: %s: not a valid identifier\n", args[i]);
			return (0);
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(args[i]);
			set_env_var(&env, tmp[0], tmp[1]);
			free_str_tab(tmp);
		}
		i++;
	}
	return (1);
}

int	set_env_var(t_envlist **env, char *key, char *value)
{
	t_envlist	*temp;
	t_envlist	*prev;

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
	temp = create_env_node(key, value);
	if (*env == NULL)
	{
		*env = temp;
		return (0);
	}
	prev->next = temp;
	return (0);
}

t_envlist	*create_env_node(char *key, char *value)
{
	t_envlist	*node;

	node = (t_envlist *) malloc(sizeof(t_envlist));
	if (node == NULL)
		return (NULL);
	node->name = ft_strdup(key);
	if (node->name == NULL)
	{
		free(node);
		return (NULL);
	}
	node->content = ft_strdup(value);
	if (node->content == NULL)
	{
		free(node->name);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

char	**get_key_value_pair(char *str)
{
	char	**ret;
	int		i;
	int		j;

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
