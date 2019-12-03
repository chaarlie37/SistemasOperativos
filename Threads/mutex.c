#include <stdio.h>
#include <pthread.h>
#define NUM 5

int buffer[NUM];
#ifdef MUTEX
    pthread_mutex_t mutex;
#endif
int a = 0;

void * escribe(void * arg){
    int a = 0;
    while(1){
        #ifdef MUTEX
            pthread_mutex_lock(&mutex);
        #endif
        for(int i = 0; i<NUM; i++){
            buffer[i] = a;
            printf("ESCRIBIENDO %d\n", i);
        }
        #ifdef MUTEX
            pthread_mutex_unlock(&mutex);
        #endif
        a++;
        printf("a++\n");
    }

    pthread_exit(NULL);
}

void * lee(void * arg){
    int iguales = 1;
    while(1){
        #ifdef MUTEX
            pthread_mutex_lock(&mutex);
        #endif
        for(int i = 1; i<NUM; i++){
            if(buffer[i] != buffer[i-1]){
                iguales = 0;
                break;
            }
        }
        if(iguales){
            printf("Son iguales\n");
        }
        else{
            printf("No son igualess\n");
        }
        #ifdef MUTEX
            pthread_mutex_unlock(&mutex);
        #endif
        iguales = 1;
        printf("------------------TERMINO LA LECTURA %d ----------------------\n", a);
    }
    //pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    pthread_t th1, th2;
#ifdef MUTEX
    pthread_mutex_init(&mutex, NULL);

#endif
    pthread_create(&th1, NULL, lee, NULL);
    //pthread_create(&th2, NULL, lee, NULL);
    while(1){
        #ifdef MUTEX
            pthread_mutex_lock(&mutex);
        #endif
        for(int i = 0; i<NUM; i++){
            buffer[i] = a;
        }
        #ifdef MUTEX
            pthread_mutex_unlock(&mutex);
        #endif
        a++;
        printf("------------------TERMINO LA ESCRITURA %d ----------------------\n", a);
    }
    return 0;
}
