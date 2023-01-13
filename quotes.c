#include "minishell.h"

int parse_quotes(char *input)
{
    int single_count = 0;
    int double_count = 0;
    int i;

    i = 0;
    while (i < strlen(input)) 
    {
        if (input[i] == '\'')
        {
            if (single_count == 0)
                single_count++;
            else
                single_count--;
        }
        else if (input[i] == '\"')
        {
            if (double_count == 0)
                double_count++;
            else
                double_count--;
        }
        else if (input[i] == '\\')
            i++;
        // else if (single_count == 0 && double_count == 0)
            // process the character as a command
        i++;
    }
    if (single_count != 0 || double_count != 0)
    {
        printf("Error: Unclosed quotes\n");
        return 0;
    }
    return 1;
}

void trim(char *str, char c)
{
    int count;
    int i;

    i = 0;
    count = 0;
    while (str[i] && i < ft_strlen(str))
    {
        if (str[i] != c)
            str[count++] = str[i];
        i++;
    }
    str[count] = '\0';
}

void update(char *str, char *end_str)
{
    int i;

    i = 0;
    while (str[i] && i < ft_strlen(str))
    {
        end_str[i] = 0;
        i++;
    }
    end_str[i] = '\0';
}

void    quotes_handler(t_cmd *cmd)
{
    t_back_c    *bcmd;
    t_exec_c    *ecmd;
    t_list_c    *lcmd;
    t_pipe_c    *pcmd;
    t_redir_c   *rcmd;
    int         i;

    i = 0;
    if(cmd == 0)
        exit(0);
    else
    {

        if(cmd->id == EXEC_ID)
        {
            ecmd = (t_exec_c *)cmd;
            while(ecmd->args[i])
            {
                if(ecmd->args[i][0] == '\'' && parse_quotes(ecmd->args[i]))
                {
                    trim(ecmd->args[i], '\'');
                    update(ecmd->args[i], ecmd->end_args[i]);
                    ecmd->expend[i] = false;
                }
                else if(ecmd->args[i][0] == '\"' && parse_quotes(ecmd->args[i]))
                {
                    trim(ecmd->args[i], '\"');
                    update(ecmd->args[i], ecmd->end_args[i]);
                    if(ecmd->args[i][0] == '$')
                        ecmd->expend[i] = true;
                }   
                i++;
            }
        }
        else if(cmd->id == REDIR_ID)
        {
            rcmd = (t_redir_c *)cmd;

            if(rcmd->file[0] == '\'' && parse_quotes(rcmd->file))
            {
                trim(rcmd->file, '\'');
                update(rcmd->file, rcmd->efile);
                rcmd->expend = false;
            }
            else if(rcmd->file[0] == '\"' && parse_quotes(rcmd->file))
            {
                trim(rcmd->file, '\"');
                update(rcmd->file, rcmd->efile);
                if(rcmd->file[0] == '$')
                    rcmd->expend = true;
            }
        }
        else if(cmd->id == PIPE_ID || cmd->id == LIST_ID)
        {
            pcmd = (t_pipe_c *)cmd;
            quotes_handler(pcmd->left);
            quotes_handler(pcmd->right);
        }
        else if(cmd->id == BACK_ID)
        {
            bcmd = (t_back_c *)cmd;
            quotes_handler(bcmd->cmd);
        }

    }
}




