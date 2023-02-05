#include "minishell.h"

// int parse_quotes(char *input)
// {
//     int single_count = 0;
//     int double_count = 0;
//     int mark = 0;
//     int i;

//     i = 0;
//     while (i < strlen(input) && !ft_strchr(SYMBOL, input[i])) 
//     {
//         // printf("input[%d]: {%c}\n", i, input[i]);
//         if(input[i] == '\'' || input[i] == '\"')
//             mark = input[i];
//         else if (input[i] == '\'')
//         {
//             if (single_count == 0)
//                 single_count++;
//             else
//                 single_count--;
//         }
//         else if (input[i] == '\"')
//         {
//             if (double_count == 0)
//                 double_count++;
//             else
//                 double_count--;
//         }
//         else if (input[i] == '\\')
//             i++;
//         // else if (single_count == 0 && double_count == 0)
//         //     process the character as a command
//         i++;
//     }
//     if(input[--i] != mark)
//         terminated("Error: Unclosed quotes\n");
//     // printf("single_count: {%d}, double_count: {%d}\n", single_count, double_count);
//     // if (single_count != 0 || double_count != 0)
//     //     terminated("Error: Unclosed quotes\n");
//     return 1;
// }

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

int is_alpha_num(int c)
{
    if ((c >= '0' && c <= '9')
        || (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z')
        || (c == '_' || c == '-'))
        return (1);
    return (0);
}

void    count_quotes(char cmd, int *single_count, int *double_count)
{
    if(cmd)
    {
        if(cmd == '\'')
            *single_count += 1;
        else if(cmd == '\"')
            *double_count += 1;
    }
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
        else if(single_count == 1 && double_count == 1 && up == 0)
            return (0);
        else
            return (1);
        it++;
    }
    return (1);
}

char *replace_str(char *str, char *orig, char *rep)
{
    char *buf;
    
    buf = NULL;
    
        if((buf = ft_strnstr(str, orig , ft_strlen(str)) - 1))
        {
            buf = ft_strjoin(ft_substr(str, 0, buf - str), rep);
            str = ft_strnstr(str, orig , ft_strlen(str)) + ft_strlen(orig);
            str = ft_strjoin(buf, str);
        }
    return (str);
}


char *trim_quotes(const char *s, size_t len)
{
    char *new_s;

    if (len >= 2 && (s[0] == '\"' && s[len - 1] == '\"'))
    {
        new_s = malloc(len - 1);
        ft_strlcpy(new_s, s + 1, len - 1);
        new_s[len - 2] = '\0';
        return new_s;
    }
    return strdup(s);
}

int get_var(char *str, int s, int len)
{
    ;
}

char    *inner_quotes(char *s, char *needle)
{
    // int it;
    // int it2;
    size_t  s_len;
    char *new_s;

    // it = 0;
    s_len = 0;
    // printf(">>S :: [%s]\n", s);
    if (new_s = ft_strnstr(s, needle, ft_strlen(s)) - 2);
    {
        printf("NEW_S :: [%s]\n", new_s);
        new_s = trim_quotes(new_s, get_var(new_s, 0, ft_strlen(needle)));
        new_s = ft_strjoin()
    }
    return(ft_strdup(s));

}

void    search_exp(char **cmd, t_envlist *list)
{
    int it;
    int it_e;
    int it_s;
    int it_v;
    int len;
    char *env_var;
    char *var;

    it = 0;
    it_s = 0;
    while(cmd[it] && it < MAX_ARG)
    {
        it_e = 0;
        while(cmd[it][it_e] && it_e < ft_strlen(cmd[it]))
        {
            var = NULL;
            len = 0;
            if(cmd[it][it_e] == '$' && validate(cmd[it]))
            {
                it_s = it_e + 1;
                while(is_alpha_num(cmd[it][++it_e]) && it_e < ft_strlen(cmd[it]))
                    len++;
                env_var = ft_substr(cmd[it], it_s, len);
                var = find_env(env_var, list);
                if(var)
                {
                    inner_quotes(cmd[it], env_var);
                    cmd[it] = replace_str(&(*cmd[it]), env_var, var);
                    // printf("ENV_VAR :: [%s]\n", env_var);
                    cmd[it] = trim_quotes(cmd[it], ft_strlen(cmd[it]));
                }
                if(cmd[it][it_e] == '\0')
                    break;
            }
            it_e++;
        }
        it++;
    }
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
            search_exp(ecmd->args, envlist);
        }
        else if(cmd->id == REDIR_ID)
        {
            rcmd = (t_redir_c *)cmd;
            search_exp(&rcmd->file, envlist);
        }
        else if(cmd->id == PIPE_ID)
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
