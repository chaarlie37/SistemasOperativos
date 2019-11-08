#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int p[2];

void manejador_hijo(int sig){
    if(sig == SIGUSR1){ // numero aleatorio
        int n;
        n = rand() % 11;
        write(p[1], &n, sizeof(int));
    }else if(sig == SIGUSR2){
        exit(0);
    }
}


int main() {
    signal(SIGUSR1, manejador_hijo);
    signal(SIGUSR2, manejador_hijo);
    int num;
    pipe(p);  // el pipe antes que el fork siempre!!!
    pid_t pid = fork();
    char buff[1024];

    srand(time(NULL));

    if(pid < 0){
        fprintf(stderr, "Error en el fork\n");
    }else if(pid == 0){
        close(p[0]);
        while(1);
    }else{

        close(p[1]);
        while(fgets(buff, 1024, stdin) != NULL){
            kill(0, SIGUSR1);
            read(p[0], &num, sizeof(int));
            printf("%d\n", num);
        }
        kill(0, SIGUSR2);
        wait(NULL);
    }
    return 0;
}
