/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:11:54 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/19 12:29:49 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

void	move_path(char *path, t_envlist **env)
{
	char	oldpwd[1024];

	if (chdir(path) != 0)
		perror("cd");
	if (getcwd(oldpwd, PATH_MAX) == NULL)
		panic("error retrieving current directory");
	if (ft_strcmp(path, "-") != 0)
		set_env_var_cd(env, "OLDPWD", oldpwd);
	set_env_var_cd(env, "PWD", getcwd(NULL, 0));
}

void	two_point(void)
{
	char	current_dir[PATH_MAX];
	char	*last_slash;

	if (getcwd(current_dir, PATH_MAX) == NULL)
		panic("error retrieving current directory");
	last_slash = ft_strrchr(current_dir, '/');
	if (last_slash == NULL)
		panic("unexpected error: current directory has no parent");
	if (last_slash == current_dir)
		go_root();
	else
	{
		*last_slash = '\0';
		if (chdir(current_dir) != 0)
			perror("cd");
	}
}

void	go_to(char **path, t_envlist **env, char **args)
{
	char	*tmp;

	tmp = *path;
	tmp = get_env_var_value(*env, "PWD");
	tmp = ft_strjoin(tmp, "/");
	tmp = ft_strjoin(tmp, args[1]);
}

void	go_root(void)
{
	if (chdir("/") != 0)
		perror("cd");
}

void	go_dash(char **path, t_envlist **env)
{
	char	*tmp;

	tmp = *path;
	tmp = get_env_var_value(*env, "OLDPWD");
	if (!tmp || *tmp == '\0' || ft_isspace(*tmp))
		panic("OLDPWD not set");
}
