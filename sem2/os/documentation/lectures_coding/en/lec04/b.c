#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    sleep(5);
    for(int i=0; i<3; i++) {
        if(fork() == 0) {
            sleep(10);
            exit(0);
        }
    }

    sleep(15);
    for(int i=0; i<3; i++) {
        wait(0);
    }

    sleep(5);
    (void)argc;
    (void)argv;
    return 0;
}
