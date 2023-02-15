#include "minishell.h"

// check if quotes are closed

int check_unclosed(char *arg)
{
    int singleQuote;
    int doubleQuote;
    int it;

    singleQuote = 0;
    doubleQuote = 0;
    it = 0;
    while(arg[it])
    {
        if(arg[it] == '\"' || arg[it] == '\'')
        {
            if(arg[it] == '\"' && doubleQuote == 0)
                doubleQuote++;
            else if (arg[it] == '\"' && doubleQuote == 1)
                doubleQuote--;
        }
        else if (arg[it] == '\'' && singleQuote == 0)
            singleQuote++;
        else if (arg[it] == '\'' && singleQuote == 1)
            singleQuote--;
        it++;
    }
    if(doubleQuote == 0 || singleQuote == 0)
        return 1;
    else
        terminated("UNCLOSED_QUOTES");
    return 0;
}

int parse_quotes(char *input)
{
    int len;

    len = ft_strlen(input);
    // printf("input   :: [%s]\n", input);
    // printf("input:1: [%c]\n", input[0]);
    // printf("input:2: [%c]\n", input[len - 1]);
    if(input[0] == '\'' || input[0] == '\"')
    {
        if (input[0] == '\'' && input[len - 1] == '\'')
            return 1;
        else if (input[0] == '\"' && input[len - 1] == '\"')
            return 1;
        else
            return 0;
    }
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

int validate(char *cmd, int *single_count, int *double_count, int flag)
{
    int len;
    int up;
    int it;

    it = 0;
    while(cmd[it - 1] == '\"' || cmd[it - 1] == '\'')
        cmd --;
    len = ft_strlen(cmd);
    up = 0;
    printf("CMD>>HERE :: [%s]\n", cmd);
    if(cmd[0] == '\'' ||cmd[len -1] == '\'')
    {
        // printf("CMD ::[%c]\n", cmd[len - 1]);
        // if(cmd[0] == '\'' && cmd[len - 1] == '\'')
        //     up++;
        printf("SINGLE_EXP ::[%d]\n", *single_count);
        printf("DOUBLE_EXP ::[%d]\n", *double_count);
        printf("FLAG>>>>>>>>> ::[%d]\n", flag);
        if (flag >= 1)
            return (1);
        else if(*single_count == 1)
            return (0);
        else if(*single_count % 2 != 0)
            return (0);
    }
    // else if (cmd[len - 1] != '\'' || cmd[len - 1] != '\"')
    //     terminated("Error: Unclosed quotes\n");
    return (1);
}


char *trim_quotes(const char *s, size_t len)
{
    char *new_s;

    // printf("LEN_TRIM :: [%zu]\n", len);
    if (len >= 2 && (s[0] == '\"' && s[len - 1] == '\"'))
    {
        // printf("S_TRIM :: [%s]\n", new_s);
        new_s = malloc(len - 1);
        ft_strlcpy(new_s, s + 1, len - 1);
        new_s[len - 2] = '\0';
        return new_s;
    }
    else if (len >= 2 && (s[0] == '\'' && s[len - 1] == '\''))
    {
        new_s = malloc(len - 1);
        ft_strlcpy(new_s, s + 1, len - 1);
        new_s[len - 2] = '\0';
        return new_s;
    }
    return strdup(s);
}

char *replace_str(char *str, char *orig, char *rep)
{
    char *buf;
    int it;
    
    buf = NULL;
    
    if((buf = ft_strnstr(str, orig , ft_strlen(str)) - 1))
    {
        buf = ft_strjoin(ft_substr(str, 0, buf - str), rep);
        str = ft_strnstr(str, orig , ft_strlen(str)) + ft_strlen(orig);
        str = ft_strjoin(buf, str);
    }
    return (str);
}

void    count(char *str, int *sing, int *dubl)
{
    while(*str)
    {
        if(*str == '\'' )
            *sing += 1;
        else if( *str == '\"')
            *dubl += 1;
        str++;
    }

}

char    *inner_quotes(char *s, char **var, int   s_len, int *sing, int *dubl)
{
    char    *new_s;
    char    *tmp_s;
    size_t  v_len;

    new_s = NULL;
    tmp_s = s;
    v_len = ft_strlen(*var) - 1;
    if (s && var && v_len)
    {
        // while(*tmp_s != '\"')
        //     tmp_s++;
        // s = tmp_s;
        if((new_s = ft_strnstr(s , *var, s_len) - 1) && *dubl)
        {
            printf("NEW_S_B :: [%c]\n", *new_s);
            printf("NEW_S_E :: [%c]\n", new_s[v_len + 2]);
            if ((*new_s == '\"') && (new_s[v_len + 2] == '\"'))
            {
                printf(">>1S :: [%s]\n\n", s);
                s = replace_str(s , (new_s + 1), "\0");
                new_s = ft_strjoin(trim_quotes(new_s , (v_len + 3)), &new_s[v_len + 3]);
                *dubl -= 1;
                s = ft_strjoin(s, new_s);
                printf(">>NEW_S :: [%s]\n\n", s);
            }
            else if ((*new_s == '\'') && (new_s[v_len + 2] == '\''))
            {
                *var = ft_strjoin("'", *var);
                *var = ft_strjoin(*var, "'");
                printf(">>VAR :: [%s]\n\n", *var);
            }
        }
        return (s);
    }
    return(ft_strdup(s));
}

char *delete_q(char *str, int len , int *sing , int *dubl)
{
    // if(sing == 1)
    //     str = trim_quotes(str, len);
    while((str[0] == '\'' || str[0] == '\"') && len > 2 &&(*sing > 0 || *dubl > 0))
    {
        if (str[0] == '\'' && str[(len - 1)] == '\'')
        {
            *sing -= 1;
            str = trim_quotes(str, len);
            len = ft_strlen(str);
            // printf(">>STR :: [%s]\n", str);
        }
        else if (str[0] == '\"' && str[(len - 1)] == '\"')
        {
            *dubl -= 1;
            str = trim_quotes(str, len);
            len = ft_strlen(str);
        }    
    }
    printf(">>STR :: [%s]\n", str);
    return (str);
}


void    search_exp(char **cmd, t_envlist *list)
{
    int it;
    int flag = 0;
    int it_e;
    int it_s;
    int it_v;
    int single_count = 0;
    int double_count = 0;
    int len;
    char *env_var;
    char *var;

    it = 0;
    it_s = 0;
    while(cmd[it] && it < MAX_ARG)
    {
        it_e = 0;
        if(!parse_quotes(cmd[it]))
            terminated("Error: Unclosed quotes\n");
        while(cmd[it][it_e] && it_e < ft_strlen(cmd[it]))
        {
            var = NULL;
            len = 0;
            count_quotes(cmd[it][it_e], &single_count, &double_count);
            if(cmd[it][it_e] == '$' && validate(&cmd[it][it_e], &single_count, &double_count,flag)
                 && check_unclosed(cmd[it]))
            {
                it_s = it_e + 1;
                while(is_alpha_num(cmd[it][++it_e]) && it_e < ft_strlen(cmd[it]))
                    len++;
                env_var = ft_substr(cmd[it], it_s, len);
                var = find_env(env_var, list);
                if(var)
                {
                    cmd[it] = replace_str(&(*cmd[it]), env_var, var);
                    // printf(">>CMD :: [%s]\n", &(*cmd[it]));
                    cmd[it] = delete_q(&(*cmd[it]), ft_strlen(cmd[it]), &single_count, &double_count);
                    flag++;
                    if(cmd[it] && (single_count > 0 || double_count > 0))
                    {
                        // printf(">>VARS2 :: [%s]\n", var);
                        while (double_count > 0)
                        {
                            // printf(">>CMD2 :: [%s]\n", cmd[it]);
                            cmd[it] = inner_quotes(&(*cmd[it]), &var ,ft_strlen(cmd[it]), &single_count, &double_count);
                        }
                        // printf(">>CMD :: [%s]\n", &(*cmd[it]));
                    }
                }
            }
            it_e++;
        }
        if(check_unclosed(cmd[it]) && (single_count > 0 || double_count > 0))
        {
            printf(">>CMD_HEREEE*** :: [%s]\n", &(*cmd[it]));
            cmd[it] = delete_q(&(*cmd[it]), ft_strlen(cmd[it]), &single_count, &double_count);
            break;
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
            // it = 0;
            ecmd = (t_exec_c *)cmd;
            search_exp(ecmd->args, envlist);
            // if (parse_quotes(ecmd->args) == 0)
            // else
            //     terminated("Error: Unclosed quotes\n");
        }
        else if(cmd->id == REDIR_ID)
        {
            rcmd = (t_redir_c *)cmd;
            // printf(">>FILENSMS<S :: [%s]\n", rcmd->file);
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
