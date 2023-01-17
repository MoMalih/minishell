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


// t_bool    to_expand(char *str ,char quote)
// {
//     int it;

//     it = 0;
//     if(quote == 's')
//     {
//         while(str[it])
//         {
//             if(str[it] == '\"')
//             {
//                 to_expand(&str[it], 'c');
//                 // trim(&str[it], '\"');
//             }
//             it++;
//         }
//         return (false);
//     }
//     else if (quote == 'd')
//     {
//         while(str[it])
//         {
//             if(str[it] == '$')
//                 return(true);
//             it++;
//         }
//     }
//     else if (quote == 'c')
//     {
//         while(str[it])
//         {
//             if(str[it] == '$')
//                 return(true);
//             it++;
//         }
//     }
//     return (false);
// }

int is_alpha_num(int c)
{
    // printf("zzzzzzzzzz\n");
    if ((c >= '0' && c <= '9')
        || (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

void    count_quotes(char cmd_char, int *single_count, int *double_count)
{
    if(cmd_char)
    {
        if(cmd_char == '\'')
            *single_count += 1;
        else if(cmd_char == '\"')
            *double_count += 1;
    }
}

char *my_strstr(const char *haystack, const char *needle) {
    int i;
    int j;
    int needle_len;
    int haystack_len;

    i = 0;
    needle_len = strlen(needle);
    haystack_len = strlen(haystack);
    while (i < haystack_len - needle_len + 1)
    {
        j = 0;
        while (j < needle_len)
        {
            if (haystack[i + j] != needle[j])
                break;
            j++;
        }
        if (j == needle_len)
            return (char *)haystack + i;
        i++;
    }
    return NULL;
}

char *find_env(char *name, t_envlist *list)
{
    t_envlist *it_list;

    it_list = list;
    while(it_list->next)
    {
        if(it_list->next->name == name)
            return it_list->content;
        it_list = it_list->next;
    }
    return NULL;
}

int    search_exp(char *cmd, t_exec_c *ecmd, t_envlist *list, int mark)
{
    int it;
    int it_e;
    int it_s;
    int single_count;
    int double_count;
    char *var;

    it_e = 0;
    it_s = 0;
    single_count = 0;
    double_count = 0;
    while(cmd[it_e] && it_e < ft_strlen(cmd))
    {
        count_quotes(cmd[it_e], &single_count, &double_count);
        if((cmd[it_e] == '$' && single_count % 2 == 0) 
            || (cmd[it_e] == '$' &&  double_count >= 0))
        {
            it_s = it_e + 1;
            while(++it_e < (ft_strlen(cmd) - it_s + 1) && is_alpha_num(cmd[it_e]))

            var = find_env(ft_substr(cmd, it_s, it_e), list);
            printf("VARR_CONTENT >> [%s]\n", var);
            it = -1;
            while(ecmd->args[it_s] && var[it])
            {
                if(it_s <= it_e)
                {
                    ecmd->args[mark][it_s] = var[++it];
                }
                else
                    ecmd->args[mark][it_s] = ecmd->args[mark][it_e];
                it_s++;
                it_e++;
            }
            // printf("EXPANSION [%s]\n", ecmd->args[mark]);

            if(!cmd[it_e])
                return (true);
        }
        it_e++;
    }
    return (false);
}

void    quotes_handler(t_cmd *cmd, t_envlist *envlist)
{
    t_back_c    *bcmd;
    t_exec_c    *ecmd;
    t_list_c    *lcmd;
    t_pipe_c    *pcmd;
    t_redir_c   *rcmd;
    int         it;

    if(cmd == 0)
        exit(0);
    else
    {
        if(cmd->id == EXEC_ID)
        {
            it = 0;
            ecmd = (t_exec_c *)cmd;
            while (ecmd->args[it] != NULL && parse_quotes(ecmd->args[it]))
            {
                // printf("CMD_>> [%s]\n", ecmd->args[it]);
                ecmd->expand[it] = search_exp(ecmd->args[it], ecmd, envlist, it);
                // if(ecmd->expand[it])
                    // my_strstr(ecmd->args[it], "$");
                it++;
            }    
        }
        else if(cmd->id == REDIR_ID)
        {
            rcmd = (t_redir_c *)cmd;
            if (parse_quotes(rcmd->file))
            {
                // rcmd->expand = search_exp(rcmd->file, rcmd, envlist);
                // printf("EXPANSION [%d]\n", rcmd->expand);
            } 
        }
        else if(cmd->id == PIPE_ID || cmd->id == LIST_ID)
        {
            pcmd = (t_pipe_c *)cmd;
            quotes_handler(pcmd->left, envlist);
            quotes_handler(pcmd->right, envlist);
        }
        else if(cmd->id == BACK_ID)
        {
            bcmd = (t_back_c *)cmd;
            quotes_handler(bcmd->cmd, envlist);
        }

    }
}




