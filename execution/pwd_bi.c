#include "sshell.h"

int pwd_bi()
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
    return 0;
}

//int pwd_bi(t_env *data)
//{
//    char buf[PATH_MAX];
//    char    *cwd;
//
//    if (data->working_dir)
//    {
//        printf("%s\n", data->working_dir);
//        return (EXIT_SUCCESS);
//    }
//    cwd = getcwd(buf, PATH_MAX);
//    if (cwd)
//    {
//        printf("%s\n", buf);
//        return (EXIT_SUCCESS);
//    }
//    perror("pwd");
//    return (EXIT_FAILURE);
//}

//int main()
//{
//	pwd_bi();
//	return 0;
//}
