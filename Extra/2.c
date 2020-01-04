#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

void foo(){
    printf("Ejecutando rutina foo(). PID: %d\n", getpid());
}

int main(){
    int i;
    pid_t pids[N];
    int fd[2];
    pipe(fd);
    for(i = 0; i<N; i++){
        pids[i] = fork();
        if(pids[i] == 0){
            break;
        }else if(pids[i] < 0){
            //error();
        }
    }

    if(pids[i] == 0){
        foo();
        int j;
        for(j = 0; j<N; j+=2){
            if(i % 2 == 0){
                close(fd[0]);
                write(fd[1], &i, sizeof(int));
                close(fd[1]);
                exit(0);
            }else{
                int aux;
                close(fd[1]);
                read(fd[0], &aux, sizeof(int));
                close(fd[1]);
                printf("Soy el PROCESO %d con PID %d, imprimo el numero %d\n", i, getpid(), aux);
                exit(0);
            }
        }
    }else if(pids[i] > 0){
        wait(NULL);
    }
    exit(0);
}
