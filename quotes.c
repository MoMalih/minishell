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
    if (c >= '0' && c <= '9')
        return (1);
    if (c >= 'a' && c <= 'z')
        return (1);
    if (c >= 'A' && c <= 'Z')
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

int    search_exp(char *cmd)
{
    int it;
    int it_e;
    int single_count;
    int double_count;
    char *str;

    it_e = 0;
    single_count = 0;
    double_count = 0;
    while(cmd[it_e] && it_e < ft_strlen(cmd))
    {
        count_quotes(cmd[it_e], &single_count, &double_count);
        if(((cmd[it_e] == '$') && single_count % 2 == 0) 
            || ((cmd[it_e] == '$') &&  double_count >= 0))
        {
            it = 0;
            while(is_alpha_num(cmd[++it_e]) && it_e < ft_strlen(cmd))
            {
                str[it] = cmd[it_e];
                printf("EXPANSION [%c]\n\n", str[it]);
                it++;
            }    
            str[it] = '\0';
            return (true);
        }
        it_e++;
    }
    return (false);
}

void    quotes_handler(t_cmd *cmd)
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
                ecmd->expand[it] = search_exp(ecmd->args[it]);
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
                rcmd->expand = search_exp(rcmd->file);
                printf("EXPANSION [%d]\n", rcmd->expand);
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




