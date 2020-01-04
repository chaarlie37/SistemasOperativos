#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int numeroLineas = 10;
    char buf[1024];

    if(argc > 2){
        printf("Error. Uso: %s -N", argv[0]);
        return 1;
    }
    if(argc == 2){
        numeroLineas = atoi(argv[1] + 1);
    }

    for(int i = 0; i<numeroLineas; i++){
        fgets(buf, 1024, stdin);
        printf("%s\n", buf);

    }

    return 0;
}
