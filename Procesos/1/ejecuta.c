#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[]) {

    int status;

    if(argc == 1){
        printf("Error. Uso: %s mandato [opciones]\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();
    if(pid < 0){
        fprintf(stderr, "Error. Falló el fork()\n");
    }
    else if(pid == 0){
        execvp(argv[1], argv + 1);
        printf("Error al ejecutar el mandato %s\n", strerror(errno));
        exit(1);
    }
    else{
        wait(&status);
        if(WIFEXITED(status) != 0){
            if(WEXITSTATUS(status) != 0){
                printf("El proceso no se ejecutó correctamente.\n");
            }
        }
        exit(0);
    }
    return 0;
}
