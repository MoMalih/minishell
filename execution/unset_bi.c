#include"sshell.h"

int unset(t_env *cmds)
{
    t_exec_c    data;
    t_envlist   envp;
    
    envp = cmds->envlist
    data = (t_exec_c *)cmds->cmd;
    if (data->args[2][0] != NULL) {
        printf(stderr, "too many arguments\n");
        return 1;
    }
    while (envp->next != NULL)
    {
        if (ft_strncmp(envp->name, data->args[1], strlen(data->args[1])) == 0) 
        {
            envp->next = envp->next->next;
            break;
        }
    }
    return 0;
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s VARNAME\n", argv[0]);
        return 1;
    }

    char *varname = argv[1];
    int i;
    for (i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], varname, strlen(varname)) == 0 && envp[i][strlen(varname)] == '=') {
            int j;
            for (j = i; envp[j] != NULL; j++) {
                envp[j] = envp[j+1];
            }
            break;
        }
    }

    return 0;
}
*/