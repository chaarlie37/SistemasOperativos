#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
  int primero = 1;
  int incremento = 1;
  int ultimo;
  switch(argc){
    case 2 :
      ultimo = atoi(argv[1]);
      break;
    case 3 :
      primero = atoi(argv[1]);
      ultimo = atoi(argv[2]);
      break;
    case 4 :
      primero = atoi(argv[1]);
      incremento = atoi(argv[2]);
      ultimo = atoi(argv[3]);
      break;
    default:
      printf("Error.");
  }
  for(int i = primero; i<=ultimo; i += incremento){
    printf("%d\n", i);
  }
  return 0;
}
