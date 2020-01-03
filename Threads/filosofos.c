#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

sem_t palillos[5];
pthread_t filosofos[5];
char f_estados[5][10] = {"", "", "", "", ""};

void * funcion(void * arg){
    int filosofo = * (int *) arg;
    while(1){
        sleep(rand() % 4 + 1);
        //printf("Filósofo %d quiere comer\n", filosofo);
        strcpy(f_estados[filosofo], "esperando");
        printf("ESTADO: 0 -> %s     1 ->  %s     2 ->  %s     3 ->  %s     4 ->  %s\n",
        f_estados[0], f_estados[1], f_estados[2], f_estados[3], f_estados[4]);
        sem_wait(&palillos[filosofo % 5]);
        sem_wait(&palillos[(filosofo + 1)  % 5]);
        //printf("Filósofo %d COMIENDO...\n", filosofo);
        strcpy(f_estados[filosofo], "comiendo");
        printf("ESTADO: 0 -> %s     1 ->  %s     2 ->  %s     3 ->  %s     4 ->  %s\n",
        f_estados[0], f_estados[1], f_estados[2], f_estados[3], f_estados[4]);
        sleep(rand() % 4 + 1);
        //printf("Filósofo %d terminó de comer\n", filosofo);
        //printf("Filósofo %d pensando...\n", filosofo);
        strcpy(f_estados[filosofo], "pensando");
        printf("ESTADO: 0 -> %s     1 ->  %s     2 ->  %s     3 ->  %s     4 ->  %s\n",
        f_estados[0], f_estados[1], f_estados[2], f_estados[3], f_estados[4]);
        sem_post(&palillos[filosofo % 5]);
        sem_post(&palillos[(filosofo + 1) % 5]);
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    int cero = 0, uno = 1, dos = 2, tres = 3, cuatro = 4;
    for(int i = 0; i<5; i++){
        sem_init(&palillos[i], 0, 1);
    }
    pthread_create(&filosofos[0], NULL, funcion, &cero);
    pthread_create(&filosofos[1], NULL, funcion, &uno);
    pthread_create(&filosofos[2], NULL, funcion, &dos);
    pthread_create(&filosofos[3], NULL, funcion, &tres);
    pthread_create(&filosofos[4], NULL, funcion, &cuatro);
    while(1);
    return 0;
}
