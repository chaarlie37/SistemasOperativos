#include <pthread.h>
#include <stdio.h>
int sum = 0;
void *suma(void *num) { // hebra
    int limite = *(int *) num;
    for(int i = 0; i <= limite; i++)
        sum += i;
    pthread_exit(NULL);
}
int main() {
    pthread_t tid;
    int N = 10;
    pthread_create(&tid, NULL, suma, (void *) &N);   // llamar a suma con un 10, hay q hacer comprobacion
    // no se puede poner el 10 directamente en vez de (void *) &N porque sino entraría por valor
    pthread_join(tid, NULL);
    printf("SUMA = %d\n", sum); // SUMA = suma de los N primeros numeros
    return 0;
}

// para compilar con threads: gcc diap57.c -o diap57 -Wall -pthread
