/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:19:03 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/19 01:47:09 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

char	*get_env_var_value(t_envlist *env, char *var)
{
	t_envlist	*tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->name, var) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env_var_cd(t_envlist **env, char *name, char *value)
{
	t_envlist	*tmp;
	char		*tmp_str;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			tmp_str = tmp->content;
			tmp->content = ft_strdup(value);
			if (tmp_str)
				free(tmp_str);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = (t_envlist *)malloc (sizeof (t_envlist));
	tmp->name = ft_strdup(name);
	tmp->content = ft_strdup(value);
	tmp->next = NULL;
	if (*env == NULL)
	{
		*env = tmp;
		return ;
	}
	tmp->next = *env;
	*env = tmp;
}

void	update_pwd_env_var(t_envlist *env, char *oldpwd, char *newpwd)
{
	set_env_var_cd(&env, "PWD", newpwd);
	set_env_var_cd(&env, "OLDPWD", oldpwd);
}

void	change_dir(t_envlist **env, char *path)
{
	char	*ret;
	char	cwd[PATH_MAX];
	char	oldpwd[PATH_MAX];

	if (chdir(path) != 0)
	{
		perror ("cd");
		return ;
	}
	if (getcwd(oldpwd, PATH_MAX) == NULL)
		panic("error retrieving current directory");
	if (getcwd(cwd, PATH_MAX) == NULL)
		panic("cd: error retrieving current directory");
	else
		ret = ft_strdup(cwd);
	update_pwd_env_var(*env, oldpwd, ret);
	free(ret);
}

int	cd_builtin(char **args, t_envlist **env)
{
	char	*path;
	char	oldpwd[PATH_MAX];

	if (!args[1] || strcmp(args[1], "~") == 0)
	{
		path = get_env_var_value(*env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			panic("HOME not set");
	}
	else if (strcmp(args[1], "-") == 0)
	{
		path = get_env_var_value(*env, "OLDPWD");
		if (!path || *path == '\0' || ft_isspace(*path))
			panic("OLDPWD not set");
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		exit (1);
	}
	if (getcwd(oldpwd, PATH_MAX) == NULL)
		panic("error retrieving current directory");
	if (strcmp(path, "-") != 0)
		set_env_var_cd(env, "OLDPWD", oldpwd);
	set_env_var_cd(env, "PWD", getcwd(NULL, 0));
	return (0);
}
