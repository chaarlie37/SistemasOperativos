#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9

void foo(){
    printf("Ejecutando rutina foo(). PID: %d\n", getpid());
}

int main(){
    int i;
    pid_t pids[N];
    int pipes[(N-1)/2][2];
    for(int i = 0; i<(N-1)/2; i++){
        pipe(pipes[i]);
    }
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
        if(i<N-1){
            if(i % 2 == 0){
                close(pipes[i/2][0]);
                write(pipes[i/2][1], &i, sizeof(int));
                close(pipes[i/2][1]);
            }else{
                int aux;
                close(pipes[(i-1)/2][1]);
                read(pipes[(i-1)/2][0], &aux, sizeof(int));
                close(pipes[(i-1)/2][1]);
                printf("Soy el PROCESO %d con PID %d, imprimo el numero %d\n", i, getpid(), aux);
            }
            exit(0);
        }
    }else if(pids[i] > 0){
        int j;
        for(j = 0; j<N; j++){
            wait(NULL);
        }
        exit(0);
    }
}
