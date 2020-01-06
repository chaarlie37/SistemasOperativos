#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 5

pthread_t filosofos[N];
int palillo[N];     // 1 es ocupado, 0 libre
pthread_mutex_t mutex;
int estado_filosofo[N];
pthread_cond_t espera[N];

char* estado(int i){
    switch(i){
        case 0 : return "pensando";
        case 1 : return "esperando";
        case 2 : return "comiendo";
    }
    return NULL;
}

void print_estado(){
    printf("Estado: 0 => %s\t1 => %s\t2 => %s\t3 => %s\t4 => %s\n", estado(estado_filosofo[0]), estado(estado_filosofo[1]), estado(estado_filosofo[2]), estado(estado_filosofo[3]), estado(estado_filosofo[4]));
}

void* funcion(void* arg){
    int id = *(int*) arg;
    while(1){
        estado_filosofo[id] = 0;
        printf("Filósofo %d pensando...\n", id);
        print_estado();
        sleep((rand() % 5) + 1);

        estado_filosofo[id] = 1;
        printf("Filósofo %d quiere comer...\n", id);
        print_estado();

        pthread_mutex_lock(&mutex);
        while(palillo[id] || palillo[(id + 1) % N]){
            pthread_cond_wait(&espera[id], &mutex);
            pthread_cond_wait(&espera[(id+1)%N], &mutex);
        }


        palillo[id] = 1;
        palillo[(id + 1) % N] = 1;

        pthread_mutex_unlock(&mutex);

        estado_filosofo[id] = 2;
        printf("Filósofo %d comiendo...\n", id);
        print_estado();
        sleep((rand() % 5) + 1);

        pthread_mutex_lock(&mutex);
        palillo[id] = 0;
        palillo[(id + 1) % N] = 0;
        pthread_cond_signal(&espera[id]);
        pthread_cond_signal(&espera[(id + 1) % N]);
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    int id[N];
    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i<N; i++){
        palillo[i] = 0;
        id[i] = i;
        pthread_cond_init(&espera[i], NULL);
        pthread_create(&filosofos[i], NULL, funcion, (void*) &id[i]);
    }
    while(1);
}
