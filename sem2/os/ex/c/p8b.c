#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd = open("a2b", O_RDONLY);
  if (fd < 0) {
    perror("error opening a2b");
    exit(0);
  }
  int fd2 = open("b2a", O_WRONLY);
  if (fd2 < 0) {
    perror("error openning b2a");
    exit(0);
  }
  int n, len;
  read(fd, &n, sizeof(int));
  for (int i = 0; i < n; i++) {
    read(fd, &len, sizeof(int));
    char *s = malloc(len);
    read(fd, s, len);
    for (int j = 0; j < len; j++) {
      if (s[j] >= 'a' && s[j] <= 'z')
        s[j] = s[j] - 'a' + 'A';
    }
    write(fd2, &len, sizeof(int));
    write(fd2, s, len);
    free(s);
  }
  close(fd);
  close(fd2);
  return 0;
}
