#include "sshell.h"

static bool is_alone(t_env *data)
{
    t_cmd *cmd;

    cmd = data->cmd;
    if (!cmd)
        return (false);
    if (cmd->next != NULL || cmd->prev != NULL)
        return (true);
    return (false);
}


int exit_bi(t_env *data, char **args)
{
    int exit_code;
    bool    alone;

    alone = is_alone(data);
}