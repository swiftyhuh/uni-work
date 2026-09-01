#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int* a = (int*)malloc(100*sizeof(int));
    a[100] = 5;
    printf("Hellow world %d\n", a[100]);
    (void)argc;
    (void)argv;
    return 0;
}
