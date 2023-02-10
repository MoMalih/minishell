#include "sshell.h"
// #include "../minishell.h"


int fork1(void)
{
  int pid;

  pid = fork();
  if(pid == -1)
    panic("fork");
  return pid;
}

void panic(char *mssg)
{
    ft_putstr_fd(mssg, 2);
    ft_putstr_fd("\n", 2);
    exit(1);
}

void runcmd(t_cmd *cmd, t_envlist *env)
{
    int p[2];
    t_back_c    *bcmd;
    t_exec_c    *ecmd;
    t_list_c    *lcmd;
    t_pipe_c    *pcmd;
    t_redir_c   *rcmd;
    char        *path;

    if (cmd == 0)
        exit(1);
    
    if (cmd->id == 1)
    {
        ecmd = (t_exec_c *)cmd;
        if (ecmd->args[0] == 0)
            exit(1);
        /*add FINDPATH*/
        path = path_finder(ecmd->args[0], env);
        execve(path, ecmd->args, env_var(env)); /*add envlist*/
        ft_putstr_fd("exec failed",2);
        //break;
    }
    else if (cmd->id == 2)
    {
        rcmd = (t_redir_c *)cmd;
        close(rcmd->fd);
        if (open(rcmd->file, rcmd->flag) < 0)
        {
            ft_putstr_fd("open failed",2);
            exit(1);
        }
        runcmd(rcmd->cmd,env);
        //break;
    }
    else if (cmd->id == 4)
    {
        lcmd = (t_list_c *)cmd;
        if (fork1() == 0)
            runcmd(lcmd->left,env);
        wait(0);
        runcmd(lcmd->right,env);
        //break;
    }
    else if (cmd->id == 3)
    {
        pcmd = (t_pipe_c *)cmd;
        if (pipe(p) < 0)
            panic("pipe");
        if (fork1() == 0)
        {
            close(1);
            dup(p[1]);
            close(p[0]);
            close(p[1]);
            runcmd(pcmd->left,env);
        }
        if (fork1() == 0)
        {
            close(0);
            dup(p[0]);
            close(p[0]);
            close(p[1]);
            runcmd(pcmd->right,env);
        }
        close(p[0]);
        close(p[1]);
        wait(0);
        wait(0);
        //break; 
    }
    else if (cmd->id == 5)
    {
        bcmd = (t_back_c *)cmd;
        if(fork1() == 0)
            runcmd(bcmd->cmd,env);
        //break;
    }
    else
        /*111*/
    exit(0);
}

char    *search_env_var(t_envlist *env, char *str)
{
    int i;
    int l;

    i = 0;
    l = strlen(str);
    while (env)
    {
        if (ft_strncmp(env->content, str, l) == 0 && env->content[l] == '=')/*should change strncmp*/
            return (env->content + l + 1);
        env = env->next;
    }
    return (NULL);
}

char *path_finder(char *key, t_envlist *lenv)
{
	char *PATH;
	char **paths;
	struct stat	buf;
	int i = 0;

	key = strjoin1("/", key);
	PATH = search_env_var(lenv, "PATH");
	paths = split1(PATH, ':');
	while (paths[i])
	{
		if (!stat(strjoin1(paths[i], key), &buf))
			return(strjoin1(paths[i], key));
		i++;
	}
	return(NULL);
}