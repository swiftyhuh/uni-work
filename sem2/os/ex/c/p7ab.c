#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd1 = open("fifo1", O_RDONLY);
  if (fd1 < 0) {
    perror("Error opening fifo1");
    exit(1);
  }
  int fd2 = open("fifo2", O_WRONLY);
  if (fd2 < 0) {
    perror("Error opening fifo2");
    exit(1);
  }

  int n;
  srandom(getpid() ^ 2);
  while (1) {
    read(fd1, &n, sizeof(int));
    printf("B received %d\n", n);
    if (n == 10)
      break;
    n = random() % 10 + 1;
    printf("B sends %d\n", n);
    write(fd2, &n, sizeof(int));
    if (n == 10)
      break;
  }
  close(fd1);
  close(fd2);

  return 0;
}
