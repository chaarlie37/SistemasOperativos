#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N 10 // revisar si esta constante es par o impar en todos los ejs!!

void foo(){
    printf("Ejecutando rutina foo(). PID: %d\n", getpid());
    exit(0);
}

int main() {
    pid_t pids[N];
    int i;
    for(i = 0; i<N; i++){
        pids[i] = fork();
        if(pids[i] == 0){
            break;
        }else if(pids[i] < 0){
            //error();
        }
    }

    if(pids[i] > 0){
        pid_t hijoMuerto;
        while(1){
            hijoMuerto = wait(NULL);
            printf("Ha muerto el proceso con PID %d.\n", hijoMuerto);
            pid_t pid = fork();
            if(pid == 0){
                foo();
            }else if(pid < 0){
                //error();
            }
        }
    }else if(pids[i] == 0){
        foo();
    }

    exit(0);
}
