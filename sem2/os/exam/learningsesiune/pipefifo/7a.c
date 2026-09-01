//7a. Write two C programs that communicate via fifo. The two processes will alternate sending random integers between 1 and 10 (inclusively) to one another until one of them sends the number 10. Print messages as the numbers are sent. One of the two processes must be responsible for creating and deleting the fifos.

//A

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    mkfifo("a2b", 0600);
    mkfifo("b2a", 0600);

    int fdwrite = open("a2b", O_WRONLY);
    int fdread = open("b2a", O_RDONLY);

    srandom(getpid());
    int nr = 0;
    while(nr != 10){
        nr = random()%10+1;
        write(fdwrite, &nr, sizeof(int));
        printf("Parent send: %d\n", nr);
        if (nr == 0)
            break;
        read(fdread, &nr, sizeof(int));
        printf("Parent received: %d\n", nr);
    }
    close(fdwrite);
    close(fdread);
    unlink("a2b");
    unlink("b2a");
    return 0;
}

