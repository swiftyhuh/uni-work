#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    printf("A %d\n", getpid());
    if(fork() == 0) {
        if(execl("./b", "./b", NULL) < 0) {
            exit(1);
        }
    }
    printf("B %d\n", getpid());
    wait(0);
    (void)argc;
    (void)argv;
    return 0;
}
