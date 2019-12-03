#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

char *cmd1[] = {"ls", "-la", 0};

int main(int argc, char const *argv[]) {
    int fd[2];
    pipe(fd);
    int pid = fork();
    if(pid == 0){   // hijo del primer comando
        close(STDOUT_FILENO);
        dup(fd[1]);
        close(fd[0]);
        execvp(cmd1[0], cmd1);
        close(fd[1]);
    }
    else{

        int pid2 = fork();
        if(pid2 == 0){      // hijo del segundo comando
            char *cmd2[] = {"tr", "d", "D", 0};
            close(fd[1]);
            close(STDIN_FILENO);
            dup(fd[0]);
            execvp(cmd2[0], cmd2);
            printf("Pruebaaaa\n");
            close(fd[0]);
        }
        else{               // padre
            wait(NULL);
        }
    }
    return 0;
}
