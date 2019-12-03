#include <stdio.h>
#include <pthread.h>
#define NUM 10000

int buffer[NUM];
#ifdef MUTEX
    pthread_mutex_t mutex;
#endif


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
            printf("No son iguales\n");
        }
        iguales = 1;
        #ifdef MUTEX
            pthread_mutex_unlock(&mutex);
        #endif

        //printf("------------------TERMINO LA LECTURA %d ----------------------\n", a);
    }
    //pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    pthread_t th1;
    int a = 0;
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
        //printf("------------------TERMINO LA ESCRITURA %d ----------------------\n", a);
    }
    return 0;
}
