#include <stdio.h>
#include <signal.h>

void f(int sgn) {
    printf("ha ha nu vreau\n");
    (void)sgn;
}


int main(int argc, char** argv) {
    signal(SIGINT, f);
    signal(SIGTERM, f);
    while(1);
    (void)argc;
    (void)argv;
    return 0;
}
