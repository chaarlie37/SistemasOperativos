#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    printf("%d\n", argc);

    char str1[] = "hola";
    printf("%s\n", str1);

    char str2[10]="";
    strcpy(str2, argv[0]);
    printf("%s\n", str2);
    printf("%s\n", str1);

    char str3[1]="\0";
    //strcpy(str3, argv[1]);
    printf("%s\n", str3);
    printf("%s\n", str1);

    char str4[sizeof(argv[2])];

    strcpy(str4, argv[2]);
    printf("%d\n", (int) sizeof(argv[2]));
    printf("%s\n", str4);
    printf("%s\n", str1);

    //str1 = "hola2";

    str1[2] = 'P';
    printf("%s\n", str1);
    return 0;
}
