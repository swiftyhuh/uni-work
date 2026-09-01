#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int p2c[2], c2p[2];
  pipe(p2c);
  pipe(c2p);

  int f = fork();

  if (f == 0) {
    close(p2c[1]);
    close(c2p[0]);

    int n, x, sum = 0;
    read(p2c[0], &n, sizeof(int));
    for (int i = 0; i < n; i++) {
      read(p2c[0], &x, sizeof(int));
      sum += x;
    }
    write(c2p[1], &sum, sizeof(int));

    close(p2c[0]);
    close(c2p[1]);
    exit(0);
  }

  close(p2c[0]);
  close(c2p[1]);

  int n = 3;
  int v[] = {10, 20, 30};
  write(p2c[1], &n, sizeof(int));
  for (int i = 0; i < n; i++)
    write(p2c[1], &v[i], sizeof(int));

  int sum;
  read(c2p[0], &sum, sizeof(int));
  printf("Sum = %d\n", sum);

  close(p2c[1]);
  close(c2p[0]);
  wait(0);
  return 0;
}
