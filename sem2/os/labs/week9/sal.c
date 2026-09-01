#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("please provide one argument\n");
    exit(0);
  }
  int fd = open(argv[1], O_RDONLY);
  printf("Test\n");
  if (-1 == fd) {
    perror("Error on open fifo");
    unlink(argv[1]);
    exit(1);
  }
  int l = 0;
  read(fd, &l, sizeof(int));
  printf("Read lenght %d\n", l);
  char *buf = malloc(sizeof(char) * (l + 1));
  int k = read(fd, buf, sizeof(char) * l);
  buf[k] = 0;

  printf("read message %s\n", buf);
  free(buf);
  close(fd);

  return 0;
}
