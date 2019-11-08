#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int i;
pid_t hijos[4] = {0, 0, 0, 0};

void manejador_hijo(int sig){
    if(sig == SIGUSR2){
        printf("Soy el proceso %d, corriendo...\n", getpid());
        sleep(1);
        if(i != 0){
            printf("Terminé. Paso el testigo al proceso %d\n", hijos[i-1]);
            kill(hijos[i-1], SIGUSR2);
        }
        else{
            printf("Terminé!\n");
        }
        exit(0);
    }
}


int main(){
    signal(SIGUSR2, manejador_hijo);

    for(i = 0; i<4; i++){
        pid_t pid = fork();
        if(pid == 0){
            pause();
        }else{
            hijos[i] = pid;
        }
    }

    kill(hijos[3], SIGUSR2);

    for(i = 0; i<4; i++){
        wait(NULL);
    }
    printf("Todos los hijos terminaron.\n");
    return 0;
}
