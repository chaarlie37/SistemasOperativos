#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>


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
        char buffcaps[1024];
        for(int i = 0; buff[i] != "\0"; i++){
            buffcaps[i] = toupper(buff[i]);
        }
        write(pipe_2[1], buffcaps, 1024);
        close(pipe_2[1]);
        close(pipe_1[0]);
    }else{
        char buff[1024];
        char buffcaps[1024];
        fgets(buff, 1024, stdin);
        close(pipe_1[0]);
        close(pipe_2[1]);
        write(pipe_1[1], buff, 1024);
        read(pipe_2[0], buffcaps, 1024);
        close(pipe_1[1]);
        close(pipe_2[0]);
        wait(NULL);
        fputs(buffcaps, stdout);
    }
    return 0;
}
