/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:19:46 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/18 04:29:28 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"sshell.h"

int	unset_builtin(char **args, t_envlist **env)
{
	t_envlist	*found;

	if (args[1] == NULL)
	{
		panic("unset: not enough arguments");
		return (1);
	}
	found = find_env_variable(args[1], env);
	if (found == NULL)
	{
		panic("unset: variable not found");
		return (1);
	}
	remove_env_variable(found, env);
	return (0);
}

t_envlist	*find_env_variable(char *name, t_envlist **env)
{
	t_envlist	*current;

	current = *env;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	remove_env_variable(t_envlist *var, t_envlist **env)
{
	t_envlist	*current;

	if (var == *env)
		*env = (*env)->next;
	else
	{
		current = *env;
		while (current != NULL && current->next != var)
			current = current->next;
		if (current != NULL)
			current->next = var->next;
	}
	free(var->name);
	free(var);
}

/*int unset_builtin(char **args, t_envlist **env)
{
    t_envlist   *temp;
    t_envlist   *prev;

    temp = *env;
    prev = *env;
    printf("%s\n",args[1]);
    if (args[1] == NULL)
    {
        panic("unset: not enough arguments");
        return (1);
    }
    while (temp != NULL)
    {
        if (ft_strcmp(temp->name, args[1]) == 0)
        {
            if (temp == *env)
            {
                *env = (*env)->next;
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp->name);
            free(temp);
            return (0);
        }
        prev = temp;
        temp = temp->next;
    }
    panic("unset: variable not found");
    return (1);
}

int unset_builtin(char **args, t_envlist *env)
{
    t_envlist   temp;
    t_envlist   prev;

    temp = env;
    prev = env;
    if (args[1] == 0)
    {
        panic("unset: not enough arguments");
        return (1);
    }
    while (temp->next != NULL)
    {
        if (ft_strcmp(temp->name, args[1]) == 0)
        {
            prev->next = temp->next;
            free(temp);
            return (0);
        }
        prev = temp;
        temp = temp->next;
    }
    if (ft_strcmp(temp->name, args[1]) == 0)
    {
        prev->next = temp->next;
        free(temp);
        return (0);
    }
    panic("unset: variable not found");
    return (1);
}*/
