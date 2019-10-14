#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    char *ruta;
    if (argc > 2) {
        printf("Error. Uso correcto: 1 ruta absoluta o relativa o ninguna para usar la variable HOME.\n");
        return 1;
    }
    if (argc == 2) {
        ruta = argv[1];
    }else{
        ruta = getenv("HOME");
        if(ruta == NULL)
		{
		  fprintf(stderr,"No existe la variable $HOME\n");
		}
    }
    if(chdir(ruta) != 0){
        printf("Error al cambiar de ruta.\n");
    }else{
        char buffer[512];
        printf("Se ha cambiado a la ruta %s correctamente.\n", getcwd(buffer, -1));
    }
    return 0;
}
