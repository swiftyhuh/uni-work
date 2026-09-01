#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    printf("PARINTE %d %d a\n", getpid(), getppid());
    for(int i=0; i<3; i++) {
        if(fork() == 0) {
            printf("FIU %d %d %d\n", getpid(), getppid(), i);
            exit(0);
        }
    }

    for(int i=0; i<3; i++) {
        wait(NULL);
    }

    printf("PARINTE %d %d b\n", getpid(), getppid());

    (void)argc;
    (void)argv;
    return 0;
}
