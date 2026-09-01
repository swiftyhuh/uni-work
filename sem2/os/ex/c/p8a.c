// 8. Write 2 C programs, A and B. A receives however many command line
// arguments and sends them to process B. Process B converts all lowercase
// letters from the received arguments to uppercase arguments and sends the
// results back to A. A reads the results, concatenates them and prints.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (0 > mkfifo("a2b", 0600)) {
    perror("Error creating a2b");
    exit(0);
  }
  if (0 > mkfifo("b2a", 0600)) {
    perror("Error creating b2a");
    exit(0);
  }
  int fd = open("a2b", O_WRONLY);
  if (fd < 0) {
    perror("Error opening a2b");
    exit(0);
  }
  int fd2 = open("b2a", O_RDONLY);
  if (fd2 < 0) {
    perror("Error opening b2a");
    exit(0);
  }
  int len, n = argc - 1;
  write(fd, &n, sizeof(int));
  for (int i = 1; i < argc; i++) {
    len = strlen(argv[i]) + 1;
    write(fd, &len, sizeof(int));
    write(fd, argv[i], len);
  }
  for (int i = 0; i < n; i++) {
    read(fd2, &len, sizeof(int));
    char *s = malloc(len);
    read(fd2, s, len);
    printf("%s\n", s);
    free(s);
  }

  close(fd);
  close(fd2);
  unlink("a2b");
  unlink("b2a");

  return 0;
}
