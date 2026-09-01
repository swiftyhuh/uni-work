#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fdread = open("a2b", O_RDONLY);
    int fdwrite = open("b2a", O_WRONLY);

    srandom(getpid());

    int nr = 0;
    while (1) {
        read(fdread, &nr, sizeof(int));
        printf("B received: %d\n", nr);

        if (nr == 10)
            break;

        nr = random() % 10 + 1;
        write(fdwrite, &nr, sizeof(int));
        printf("B sent: %d\n", nr);

        if (nr == 10)
            break;
    }

    close(fdread);
    close(fdwrite);

    (void)argc;
    (void)argv;
    return 0;
}
