#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t sem;
int d = 0;
int c = 0;

void * funcion(void *arg){
    //sleep(1);
    sem_wait(&sem);
    c = * (int *) arg;
    for(int i = 0; i<100; i++){
        d++;
        printf("%d\n", d);
    }
    printf("Imprimiendo el metodo %d\n", c);
    //a++;
    sleep(1);
    sem_post(&sem);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    pthread_t tid1;
    pthread_t tid2;
    int a = 1;
    int b = 2;
    sem_init(&sem, 0, 1);
    pthread_create(&tid1, NULL, funcion, &a);
    pthread_create(&tid2, NULL, funcion, &b);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    sem_destroy(&sem);
    printf("%d\n", d);
    return 0;
}
