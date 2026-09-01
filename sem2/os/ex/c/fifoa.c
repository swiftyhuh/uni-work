#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int a2b, b2a, n;

  mkfifo("a2b", 0600);
  mkfifo("b2a", 0600);

  a2b = open("a2b", O_WRONLY);
  b2a = open("b2a", O_RDONLY);

  n = 5;
  write(a2b, &n, sizeof(int));

  read(b2a, &n, sizeof(int));
  printf();
}
