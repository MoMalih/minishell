#include <stdio.h>
#include <unistd.h>

//int change_directory(const char *path) {
//    if (chdir(path) != 0) {
//        perror("chdir");
//        return 1;
//    }
//    char cwd[1024];
//    if (getcwd(cwd, sizeof(cwd)) == NULL) {
//        perror("getcwd");
//        return 1;
//    }
//    printf("Changed directory to %s\n", cwd);
//    return 0;
//}
//
//int main(int argc, char *argv[]) {
//    if (argc != 2) {
//        printf("Usage: cd path\n");
//        return 1;
//    }
//    char *path = argv[1];
//    return change_directory(path);
//}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
    int i;
    for (i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
    return 0;
}
