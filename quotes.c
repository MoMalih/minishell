#include "minishell.h"
// void update(char *str, char *end_str)
// {
//     int i;

//     i = 0;
//     while (str[i] && i < ft_strlen(str))
//     {
//         end_str[i] = 0;
//         i++;
//     }
//     end_str[i] = '\0';
// }

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

// delete the quotes leaving everything inside

char *trim(char *str, char c)
{
   int it;
    int it2;

    it = 0;
    it2 = 0;
    while(str[it])
    {
        if(str[it] == c)
        {
            it++;
            continue;
        }
        str[it2] = str[it];
        it++;
        it2++;
    }
    str[it2] = '\0';
    return (str);
}


t_bool    to_expand(char *str ,char quote)
{
    int it;

    it = 0;
    if(quote == 's')
    {
        while(str[it])
        {
            if(str[it] == '\"')
            {
                to_expand(&str[it], 'c');
                trim(&str[it], '\"');
            }
            it++;
        }
        // trim(str, '\'');
        return (false);
    }
    else if (quote == 'd')
    {
        while(str[it])
        {
            if(str[it] == '$')
                return(true);
            it++;
        }
        // trim(str, '\"');
    }
    else if (quote == 'c')
    {
        while(str[it])
        {
            if(str[it] == '$')
                return(true);
            it++;
        }
        trim(str, '\"');
    }
    return (false);
}

void    search_exp(t_exec_c *ecmd)
{
    int it;
    int it2;
    char *str;

    it = 0;
    while(ecmd->args[it])
    {
        it2 = 0;
        str = ecmd->args[it];
        while(str[it2])
        {
            if(str[it2]== '\'')
            {
                ecmd->args[it] =  trim(&str[it2], '\'');
                ecmd->expend[it] = to_expand(ecmd->args[it], 's');    
            }
            else if(str[it2] == '\"')
            {
                ecmd->args[it] = trim(&str[it2], '\"');
                ecmd->expend[it] = to_expand(ecmd->args[it], 'd');    
            }   
        }
        it++;
    }

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
                if(parse_quotes(ecmd->args[i]))
                {
                    search_exp(ecmd);
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
                rcmd->expend = to_expand(rcmd->file, 's');    
            }
            else if(rcmd->file[0] == '\"' && parse_quotes(rcmd->file))
            {
                trim(rcmd->file, '\"');
                rcmd->expend = to_expand(rcmd->file, 'd');    
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




