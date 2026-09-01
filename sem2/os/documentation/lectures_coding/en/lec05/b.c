#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    printf("C %d\n", getpid());
    (void)argc;
    (void)argv;
    return 0;
}
