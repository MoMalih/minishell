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
        terminated("Error: Unclosed quotes\n");
    return 1;
}

// delete the quotes leaving everything inside

// char *trim(char *str, char c)
// {
//    int it;
//     int it2;

//     it = 0;
//     it2 = 0;
//     while(str[it])
//     {
//         if(str[it] == c)
//         {
//             it++;
//             continue;
//         }
//         str[it2] = str[it];
//         it++;
//         it2++;
//     }
//     str[it2] = '\0';
//     return (str);
// }


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
                // trim(&str[it], '\"');
            }
            it++;
        }
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
    }
    else if (quote == 'c')
    {
        while(str[it])
        {
            if(str[it] == '$')
                return(true);
            it++;
        }
    }
    return (false);
}

int is_alpha_num(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        return 1;
    return 0;
}

void    search_exp(t_exec_c *ecmd)
{
    int it;
    int it_e;
    int it_s;
    char *str;


    it = 0;
    while(ecmd->args[it] && it <= MAX_ARG && parse_quotes(ecmd->args[it]))
    {
        it_e = 0;
        while(ecmd->args[it][it_e] && ecmd->args[it][it_e] != '\'')
        {
            // printf("it2 - it3 ->> [%d]\n", it_e);
            if(ecmd->args[it][it_e] == '$')
            {
                it_s = it_e + 1;
                // printf("NUMM >>>> [%d]\n", it_e);
                while(ecmd->args[it][it_e]
                        && (ecmd->args[it][it_e] != '\'' || ecmd->args[it][it_e] == '\"'))
                {
                    printf("ALPHA >>>> [%d]\n", it_e);
                    it_e++;
                }
                while(it_s <= it_e)
                {
                    str[it_s] = ecmd->args[it][it_s];
                    it_s++;
                }
                // printf("STRI_EXP >>>> [%c]\n", str[len - 1]);
                // ecmd->expand[it] = true;
            }
            it_e++;
        }
        str[it_e] = '\0';
        it++;
        // printf("it3 >> [%d]\n", it3);
        // printf("len >> [%d]\n", (it3 - it2 + 1));
    }

    // printf("EXPANSION ZMLA>>>>>> [%s]", str);

            // else if(str[it2]== '\'')
            //     ecmd->expand[it] = to_expand(ecmd->args[it], 's');
            // else if(str[it2] == '\"')
            //     ecmd->expand[it] = to_expand(ecmd->args[it], 'd');
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
        // printf("START\n");
        if(cmd->id == EXEC_ID)
        {
            ecmd = (t_exec_c *)cmd;
            search_exp(ecmd);
        }
        else if(cmd->id == REDIR_ID)
        {
            rcmd = (t_redir_c *)cmd;
            // if(rcmd->file[0] == '\'' && parse_quotes(rcmd->file))
            // {
            //     // trim(rcmd->file, '\'');
            //     rcmd->expand = to_expand(rcmd->file, 's');
            // }
            // else if(rcmd->file[0] == '\"' && parse_quotes(rcmd->file))
            // {
            //     // trim(rcmd->file, '\"');
            //     rcmd->expand = to_expand(rcmd->file, 'd');
            // }
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




