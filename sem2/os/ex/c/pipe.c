#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int p2c[2], c2p[2];
  pipe(p2c);
  pipe(c2p);

  int f = fork();

  if (f == -1) {
    perror("fork");
    exit(1);
  } else if (f == 0) {
    // CHILD
    close(p2c[1]); // child reads from p2c
    close(c2p[0]); // child writes to c2p

    int x;
    read(p2c[0], &x, sizeof(int));

    x = x * 2;

    write(c2p[1], &x, sizeof(int));

    close(p2c[0]);
    close(c2p[1]);
    exit(0);
  } else {
    // PARENT
    close(p2c[0]); // parent writes to p2c
    close(c2p[1]); // parent reads from c2p

    int x = 7;
    write(p2c[1], &x, sizeof(int));

    read(c2p[0], &x, sizeof(int));
    printf("Result = %d\n", x);

    close(p2c[1]);
    close(c2p[0]);
    wait(0);
  }

  return 0;
}
