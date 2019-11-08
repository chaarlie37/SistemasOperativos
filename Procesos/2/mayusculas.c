#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char const *argv[]) {
    int pipe_1[2];
    int pipe_2[2];
    pipe(pipe_1);
    pipe(pipe_2);
    pid_t pid = fork();
    if (pid < 0){
        fprintf(stderr, "Error en el fork.\n");
    }else if (pid == 0){
        char buff[1024];
        close(pipe_1[1]);
        close(pipe_2[0]);
        read(pipe_1[0], buff, 1024);
        while(strcmp(buff, "\n")){
            char buffcaps[1024];
            int i = 0;
            while(buff[i] != '\0'){
                buffcaps[i] = toupper(buff[i]);
                i++;
            }
            buffcaps[i] = '\0';
            write(pipe_2[1], buffcaps, 1024);
            read(pipe_1[0], buff, 1024);
        }

        close(pipe_2[1]);
        close(pipe_1[0]);
    }else{
        char buff[1024];
        char buffcaps[1024];
        close(pipe_1[0]);
        close(pipe_2[1]);
        fgets(buff, 1024, stdin);
        while (strncmp(buff, "\n", 1) != 0) {
            // por que strcmp no vale???????
            //printf("Palabra a pasar: %s %d\n", buff, strncmp(buff, "\n", 1));
            write(pipe_1[1], buff, 1024);
            read(pipe_2[0], buffcaps, 1024);
            fputs(buffcaps, stdout);
            strcpy(buff, "");
            fgets(buff, 1024, stdin);
        }
        close(pipe_1[1]);
        close(pipe_2[0]);
        wait(NULL);
    }
    return 0;
}
