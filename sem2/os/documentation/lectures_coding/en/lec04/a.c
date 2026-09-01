#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    printf("a %d %d\n", getpid(), getppid());
    for(int i=0; i<3; i++) {
        printf("w %d %d\n", getpid(), getppid());
        if(fork() == 0) {
            printf("c %d %d %d\n", getpid(), getppid(), i);
            exit(0);
        }
    }

    for(int i=0; i<3; i++) {
        wait(0);
    }

    printf("b %d %d\n", getpid(), getppid());
    (void)argc;
    (void)argv;
    return 0;
}
