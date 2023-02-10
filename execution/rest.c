#include "sshell.h"

void cd(char *path) {
    char cwd[1024];
    if (path[0] == '/') {
        // Absolute path
        chdir(path);
    } else {
        // Relative path
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        strcat(cwd, path);
        chdir(cwd);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: cd path\n");
        return 1;
    }
    
    cd(argv[1]);
    return 0;
}
