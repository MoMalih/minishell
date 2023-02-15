#include "sshell.h"

void cd_builtin(char **args, t_envlist *env)
{
    char *path;

    if (args[1] == 0)
        path = search_env_var(env, "HOME");
    if (args[2])
        panic("cd: too many arguments");
    if (ft_strncmp(args[1], "-", 2) == 0)
    {
        path = search_env_var(env, "OLDPWD");
        if (path == 0)
            panic("cd: OLDPWD not set");
    }
    else
        path = args[1];
    if (chdir(path) < 0)
        panic("chdir failed");
}