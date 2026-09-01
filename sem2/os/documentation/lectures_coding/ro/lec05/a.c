#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    printf("A %d\n", getpid());
    if(fork() == 0) {
        if(execl("/bin/ls", "/bin/ls", "-a", ".", NULL) < 0) {
            perror("execl nu a mers");
            exit(1);
        }
    }
    printf("B %d\n", getpid());
    wait(0);
    (void)argc;
    (void)argv;
    return 0;
}
