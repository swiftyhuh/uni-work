#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("please provide two arguments\n");
    exit(0);
  }
  if (mkfifo(argv[1], 0600) < 0) {
    perror("Error n create fifo");
    exit(1);
  }

  int fd = open(argv[1], O_WRONLY);
  printf("Test\n");
  if (-1 == fd) {
    perror("Error on open fifo");
    unlink(argv[1]);
    exit(1);
  }

  int l = strlen(argv[2]);
  write(fd, &l, sizeof(int));
  write(fd, argv[2], sizeof(char) * l);

  close(fd);
  unlink(argv[1]);

  return 0;
}
