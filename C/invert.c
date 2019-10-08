
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  for(int i = argc-1; i>0; i--){
    int longitud = strlen(argv[i]);
    for(int j = longitud; j>=0; j--){
      printf("%c", argv[i][j]);
    }
    printf(" ");
  }
  printf("\n");
  return 0;
}
