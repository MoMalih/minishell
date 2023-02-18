/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:19:03 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/17 21:19:09 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

static void	update_pwd_env_var(t_envlist *env, char *oldpwd, char *newpwd)
{
	char *key;
	char *value;

	// Update PWD environment variable
	key = ft_strdup1("PWD");
	value = ft_strdup1(newpwd);
	set_env_var_cd(&env, key, value);

	// Update OLDPWD environment variable
	key = ft_strdup1("OLDPWD");
	value = ft_strdup1(oldpwd);
	set_env_var_cd(&env, key, value);
}

static void	change_dir(t_envlist **env, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];
	char	oldpwd[PATH_MAX];

	
	if (getcwd(oldpwd, PATH_MAX) == NULL)
		panic("error retrieving current directory");
	if (chdir(path) != 0)
		terminated("didn't find path");
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		panic("cd: error retrieving current directory");
		ret = ft_strjoin(oldpwd, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free(tmp);
	}
	else
		ret = ft_strdup1(cwd);
	printf("dkhl hna");
	update_pwd_env_var(*env, oldpwd, ret);
	free(ret);
}

/*int	cd_builtin(char **args, t_envlist **env)
{
	char	*path;

	if (!args[1] || ft_strequ(args[1], "~"))
	{
		path = get_env_var_value(*env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			panic("HOME not set");
		return (!change_dir(env, path));
	}
	else if (ft_strequ(args[1], "-"))
	{
		path = get_env_var_value(*env, "OLDPWD");
		if (!path || *path == '\0' || ft_isspace(*path))
			panic("OLDPWD not set");
		return (!change_dir(env, path));
	}
	else if (ft_strequ(args[1], "."))
		return (1);
	else if (ft_strequ(args[1], ".."))
	{
		if (chdir("..") != 0)
			return (chdir_errno_mod(".."));
		char cwd[PATH_MAX];
		if (getcwd(cwd, PATH_MAX) == NULL)
			panic("error retrieving current directory");
		update_pwd_env_var(*env, ".", cwd);
		return (1);
	}
	else if (args[1][0] == '/')
		return (!change_dir(env, args[1]));
	else
	{
		char *cwd = get_env_var_value(*env, "PWD");
		if (!cwd || *cwd == '\0' || ft_isspace(*cwd))
			panic("PWD not set");
		path = ft_strjoin(cwd, "/");
		char *tmp = path;
		path = ft_strjoin(path, args[1]);
		free(tmp);
		return (!change_dir(env, path));
	}
}
*/

char	*get_env_var_value(t_envlist *env, char *var)
{
	t_envlist	*tmp;
	// char		*tmp_var;

	// tmp_var = ft_strjoin(var, "=");
	// if (!tmp_var)
	// 	return (NULL);
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->name, ft_strlen(var)) == 0)
		{
			// free_ptr(tmp_var);
			return (tmp->content);
		}
		tmp = tmp->next;
	}
	// free_ptr(tmp_var);
	return (NULL);
}

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

/*static bool	change_dir(char *path, t_envlist **envlist, char *value)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (0);
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		panic("cd: error retrieving current directory");
		ret = ft_strjoin(get_env_var_value(*envlist, "PWD"), "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		ret = ft_strdup1(cwd);
	set_env_var_cd_cd(envlist, "OLDPWD", get_env_var_value(*envlist, "PWD"));
	set_env_var_cd_cd(envlist, "PWD", ret);
	return (1);
}*/

bool		cd_builtin(char **args, t_envlist **envlist)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var_value(*envlist, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			panic("HOME not set");
		
	}
	if (args[2])
		panic("too many arguments");
	// if (ft_strncmp(args[1], "-", 1) == 0)
	// {
	// 	path = get_env_var_value(*envlist, "OLDPWD");
	// 	if (!path)
	// 		panic("OLDPWD not set");
	// 	change_dir(envlist, path);
	// }
	change_dir(envlist, path);
	printf(">>>[%s]\n",path);
	printf(">>>>path[%s]\n",path);
	//chdir(path);
	//change_dir(envlist, args[1]);
}

void set_env_var_cd(t_envlist **env, char *name, char *value)
{
    t_envlist *tmp = *env;
    char *tmp_str;

    while (tmp)
    {
        if (strcmp(tmp->name, name) == 0)
        {
            tmp_str = tmp->content;
            tmp->content = ft_strdup(value);
            if (tmp_str)
                free(tmp_str);
            return ;
        }
        tmp = tmp->next;
    }
    tmp = create_env_node(name, value);
    //add_env_node(env, tmp, value);
}

bool ft_isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

char	*ft_strdup1(const char *s1)
{
	char	*dst;
	size_t	len;

	len = 0;
	while (s1[len])
		len++;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		dst[len] = s1[len];
		len++;
	}
	dst[len] = '\0';
	return (dst);
}

int ft_strequ(char *s1, char *s2)
{
    if (!s1 || !s2)
        return (0);
    return ((ft_strcmp(s1, s2) == 0));
}

/*t_envlist	*create_new_env_node(char *name, char *content)
{
	t_envlist	*new_node;

	new_node = malloc(sizeof(t_envlist));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	return (new_node);
}*/

void	add_env_node(t_envlist **head, char *name, char *content)
{
	t_envlist	*new_node;

	if (new_node == NULL)
		panic("Memory allocation error");
	if (*head == NULL)
		*head = new_node;
	else
	{
		new_node->next = *head;
		*head = new_node;
	}
}