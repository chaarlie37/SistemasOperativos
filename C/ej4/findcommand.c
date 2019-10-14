#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    if(argc != 2){
        printf("Error. Uso: %s mandato\n", argv[0]);
        return 1;
    }
    char *path = getenv("PATH");
    char *mandato = argv[1];
    char *token = strtok(path, ":");
    int encontrado = 1;
    while(token != NULL && encontrado == 1){
        if(consultarMandato(token, mandato) != -1){
            printf("El mandato %s está en el directorio %s\n", mandato, token);
            encontrado = 0;
        }
        token = strtok(NULL, ":");
    }
    if (encontrado == 1) {
        printf("No se ha encontrado el mandato %s en la variable $PATH.\n", mandato);
    }
    return 0;
}

int consultarMandato(char *dir, char *man){
    chdir(dir);
    return access(man, X_OK);
}
