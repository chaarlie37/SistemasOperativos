#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    if(argc == 1){
        printf("Error. Uso: %s mandato [opciones]\n", argv[0]);
        return 1;
    }
    pid_t pid = fork();
    if(pid < 0){
        fprintf(stderr, "Error. Falló el fork()\n");
    }
    else if(pid == 0){
        char mandato[1024];
        strcpy(mandato, argv[1]);
        for(int i = 2; i<argc; i++){
            strcat(mandato, " ");
            strcat(mandato, argv[i]);
        }
        execvp(mandato);
        exit(0);
    }
    else{
        waitpid(pid, NULL, 0);
        exit(0);
    }
    return 0;
}
