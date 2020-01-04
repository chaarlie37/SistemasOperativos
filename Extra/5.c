#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 6

pthread_t threads[N];
int i;
int tids[N];
int num[N/2];
sem_t sem[N/2];

void foo(int a){
    printf("Ejecutando rutina foo(). TID: %d\n", a);
}

void* escribe(void* arg){
    int k = * (int*) arg;
    foo(k);
    num[k/2] = k;
    printf("Soy el thread %d\n", k);
    sem_post(&sem[k/2]);
    pthread_exit(NULL);
}

void* lee(void* arg){
    int k = * (int*) arg;
    foo(k);
    sem_wait(&sem[(k-1)/2]);
    printf("Soy el Thread %d y he recibido el número %d\n", k, num[(k-1) / 2]);

    pthread_exit(NULL);
}

int main() {

    for(i = 0; i<N-1; i+=2){
        sem_init(&sem[i/2], 0, 0);
        tids[i] = i;
        pthread_create(&threads[i], NULL, escribe, (void*) &tids[i]);
        tids[i+1] = i+1;
        pthread_create(&threads[i+1], NULL, lee, (void*) &tids[i+1]);
    }


    for(i = 0; i<N; i++){
        pthread_join(threads[i], NULL);
    }

    for(i = 0; i<N/2; i++){
        sem_destroy(&sem[i]);
    }

    return 0;
}
