#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


#define N 5


void foo(){
    printf("Ejecutando rutina foo(). PID: %d\n", getpid());
    exit(0);
}

int main() {
    int i;
    pid_t pids[N];
    for(i = 0; i<N; i++){
        pids[i] = fork();
        if(pids[i] == 0){
            break;
        }else if(pids[i] < 0){
            //error();
        }
    }

    if(pids[i] == 0){   // hijo
        foo();
    }
    else if(pids[i] > 0){   // padre
        while (1) {
            pid_t hijoMuerto;
            hijoMuerto = wait(NULL);
            if(hijoMuerto % 2 != 0){
                printf("Ha muerto el proceso con PID %d. Es impar. Creo dos procesos.\n", hijoMuerto);
                pid_t pid1, pid2;
                pid1 = fork();
                if(pid1 == 0){
                    foo();
                }else if(pid1 > 0){
                    pid2 = fork();
                    if(pid2 == 0){
                        foo();
                    }else if(pid2 < 0){
                        //error();
                    }
                }else{
                    //error();
                }
            }
        }
    }else{
        //error();
    }
    return 0;
}
