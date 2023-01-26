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
        // printf("input[%d]: {%c}\n", i, input[i]);
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
    // printf("single_count: {%d}, double_count: {%d}\n", single_count, double_count);
    if (single_count != 0 || double_count != 0)
        terminated("Error: Unclosed quotes\n");
    return 1;
}

// delete the quotes leaving everything inside

// char *trim_quotes(char *str, int *sgl, int *dbl)
// {
//     int i;
//     int j;
//     char *new_str;

//     i = 0;
//     j = 0;
//     new_str = malloc(sizeof(char) * (strlen(str) - 1));
//     if (str[i] == '\'' || str[i] == '\"')
//         i++;
//     while (str[i])
//     {
//         new_str[j] = str[i];
//         i++;
//         j++;
//     }
//     if (str[i] == '\'' || str[i] == '\"')
//         i++;
//     new_str[j] = '\0';
//     return new_str;
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
        || (c >= 'A' && c <= 'Z')
        || (c == '_' || c == '-'))
        return (1);
    return (0);
}

void    count_quotes(char cmd, int *single_count, int *double_count)
{
    // int it;

    // it = 0;
    // while(cmd[it] && it < ft_strlen(cmd))
    // {

        if(cmd)
        {
            if(cmd == '\'')
                *single_count += 1;
            else if(cmd == '\"')
                *double_count += 1;
        }
    // }
}

char    *find_env(char *name, t_envlist *list)
{
    t_envlist   *it_list;

    it_list = list;
    while(it_list->next && name && it_list->name)
    {
        if(ft_strlen(it_list->name) == ft_strlen(name))
        {
            if(!ft_strncmp(it_list->name, name, ft_strlen(name)))
                return (it_list->content);
        }
        it_list = it_list->next;
    }
    return NULL;
}

int validate(char *cmd)
{
    int it;
    int single_count;
    int double_count;
    int up;

    it = 0;
    up = 0;
    single_count = 0;
    double_count = 0;
    while(cmd[it] && it < ft_strlen(cmd))
    {
        if(cmd[it] == '\"' && single_count == 0)
            up++;
        count_quotes(cmd[it], &single_count, &double_count);
        if(single_count == 1 && double_count == 0)
            return (0);
        else if(single_count == 0 && double_count == 1)
            return (1);
        else if(single_count == 1 && double_count == 1 && up >= 1)
            return (1);
        else if(single_count == 1 && double_count == 1 && up == 0)
            return (0);
        else if(single_count == 0 && double_count == 0)
            return (1);
        it++;
    }
    return (1);
}

void    search_exp(char *cmd, t_exec_c *ecmd, t_envlist *list, int mark)
{
    int it_e;
    int it_s;
    int len;
    char *var;

    it_e = 0;
    it_s = 0;
    while(cmd[it_e] && it_e < ft_strlen(cmd))
    {
        // count_quotes(cmd[it_e], &single_count, &double_count);
        var = NULL;
        len = 0;
        if(cmd[it_e] == '$' && validate(cmd))
        {
            it_s = it_e + 1;
            while(is_alpha_num(cmd[++it_e]) && it_e < ft_strlen(cmd))
                len++;
            // printf("STR_QUO >> [%s]\n", ft_substr(cmd, it_s, len));
            var = find_env(ft_substr(cmd, it_s, len), list);
            if (var)
                printf("VAR_QUO >> [%s]\n", var);
            if(cmd[it_e] == '$' && validate(cmd))
                it_e--;
            // it = -1;
            // while(ecmd->args[it_s] && var[it])
            // {
            //     if(it_s <= it_e)
            //     {
            //         ecmd->args[mark][it_s] = var[++it];
            //     }
            //     else
            //         ecmd->args[mark][it_s] = ecmd->args[mark][it_e];
            //     it_s++;
            //     it_e++;
            // }
            // printf("EXPANSION [%s]\n", ecmd->args[mark]);
            // if(ecmd->expand[mark] == true)
            //     search_exp(&cmd[it_e], ecmd, list, mark);

        }
        it_e++;
    }
    // if(ecmd->expand[mark] == true)
    //         search_exp(&cmd[it_e], ecmd, list, mark);
    // return (false);
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
            // if(parse_quotes(ecmd->args[it]))
            // {
                while (ecmd->args[it] != NULL)
                {
                    search_exp(ecmd->args[it], ecmd, envlist, it);
                    // printf("CMD_>> [%s]\n", ecmd->args[it]);
                    // if(ecmd->expand[it])
                        // my_strstr(ecmd->args[it], "$");
                    it++;
                }    
            // }
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




