#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {

    int numeroLineas = 10;

    if(argc > 2){
        printf("Error. Uso incorrecto: %s -N", argv[0]);
        return 1;
    }
    if(argc == 2){
        numeroLineas = atoi(argv[1]);
    }

    char lineas[1024][1024];
    char buff[1024];
    int i = 0;
    while(fgets(buff, 1024, stdin)){
        lineas[i][0]=buff;
        printf("%s\n", lineas[i]);
        i++;
    }

    for(int j = i; j>0; j--){
        printf("%s\n", lineas[j]);
    }

    return 0;
}
