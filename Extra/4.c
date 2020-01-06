#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
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
    FILE* pipes[(N-1)/2];

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
                char nombre[2];
                FILE * fd;
                sprintf(nombre, "%d", i/2);
                if(mkfifo(nombre, S_IWUSR | S_IRUSR)){
                    //error();
                }
                //pipes[i/2] = fopen(nombre, "w");
                fd = fopen(nombre, "w");
                char buffer[2];
                sprintf(buffer, "%d", i);
                fputs(buffer, fd);
                fflush(fd);
                fclose(fd);
            }else{
                char nombre[2];
                sprintf(nombre, "%d", (i-1)/2);
                if(mkfifo(nombre, S_IWUSR | S_IRUSR)){
                    //error();
                }
                FILE* fd = fopen(nombre, "r");
                char buffer[2];
                while(fgets(buffer, 2*sizeof(char), fd) == NULL);   // mientras que lo que lea sea nulo, lee otra vez
                fclose(fd);
                printf("Soy el PROCESO %d con PID %d, imprimo el numero %s\n", i, getpid(), buffer);
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
