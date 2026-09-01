/* Create a C program that generates N random integers (N given at the command
 * line). It then creates a child, sends the numbers via pipe. The child
 * calculates the average and sends the result back.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Please provide exactl one argument.\n");
    exit(1);
  }

  int p2c[2], c2p[2];
  pipe(p2c);
  pipe(c2p);
  int f = fork();
  if (f == -1) {
    perror("Error on fork ");
    exit(1);
  } else if (f == 0) {
    close(p2c[1]);
    close(c2p[0]);
    int n;
    read(p2c[0], &n, sizeof(int));
    int x;
    float avg = 0;

    for (int i = 0; i < n; i++) {
      read(p2c[0], &x, sizeof(int));
      avg += x;
    }
    avg = avg / n;
    write(c2p[1], &avg, sizeof(float));
    close(p2c[0]);
    close(c2p[1]);
    exit(0);
  }
  int x, n = atoi(argv[1]);
  float avg = -1;
  close(p2c[0]);
  close(c2p[1]);
  srandom(time(0));
  write(p2c[1], &n, sizeof(int));
  for (int i = 0; i < n; i++) {
    x = random() % 100;
    printf("Parent generated %d\n", x);
    write(p2c[1], &x, sizeof(int));
  }
  read(c2p[0], &avg, sizeof(float));
  printf("Average is %f\n", avg);
  close(p2c[1]);
  close(c2p[0]);
  wait(0);

  return 0;
}
