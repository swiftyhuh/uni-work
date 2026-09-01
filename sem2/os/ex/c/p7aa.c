#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (mkfifo("fifo1", 0600) < 0) {
    perror("Error creating fifo1\n");
    exit(1);
  }
  if (mkfifo("fifo2", 0600) < 0) {
    perror("Error creating fifo2\n");
    exit(1);
  }

  int fd1 = open("fifo1", O_WRONLY);
  if (fd1 < 0) {
    perror("Error openin fifo1\n");
    exit(1);
  }
  int fd2 = open("fifo2", O_RDONLY);
  if (fd2 < 0) {
    perror("Error on opening fifo2");
    exit(1);
  }

  int n;
  srandom(getpid() ^ 2);
  while (1) {
    n = random() % 10 + 1;
    printf("A sends %d\n", n);
    write(fd1, &n, sizeof(int));

    if (n == 10)
      break;

    read(fd2, &n, sizeof(int));
    printf("A received %d\n", n);
    if (n == 10)
      break;
  }
  close(fd1);
  close(fd2);
  unlink("fifo1");
  unlink("fifo2");
  return 0;
}
