#include "sshell.h"


int env_bi(t_env *data)
{
    int i;
    t_exec_c args;
    t_envlist   temp;

    i = 0;
    args = (t_exec_c *)data->cmd;
    temp = data->envlist;
    if (args && arg[1])
    {
        printf("too many arguments\n");
        return (2)
    }
    if (!temp)
        return(EXIT_FAILURE);
    while(temp->next != NULL)
    {
        printf("%s = %s\n", temp->name, temp->content);
        temp = temp->next;
    }
    /*if (env)
		printf("%s = %s\n", temp->name, temp->content);
    */
    return (EXIT_SUCCESS);
}