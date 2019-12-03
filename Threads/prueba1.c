#include <stdio.h>
#include <pthread.h>
//Variable compartida
volatile int j = 0;
void *th_func1(void *arg) {
int i;
for(i = 0; i < 10000; i++)
j = j + 1;
pthread_exit(NULL);
}
int main() {
pthread_t th1, th2;
pthread_create(&th1, NULL, th_func1, NULL);
pthread_create(&th2, NULL, th_func1, NULL);
pthread_join(th1, NULL);
pthread_join(th2, NULL);
printf("j = %d\n", j); // OJO: ¿j vale 20000?
}
