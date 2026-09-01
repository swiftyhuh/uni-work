// 7. Write a C program that creates two child processes. The two child
// processes will alternate sending random integers between 1 and 10
// (inclusively) to one another until one of them sends the number 10. Print
// messages as the numbers are sent.

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int c1toc2[2], c2toc1[2];
  pipe(c1toc2);
  pipe(c2toc1);
  int f = fork();
  if (f == 0) {
    srandom(getpid());
    close(c2toc1[1]);
    close(c1toc2[0]);

    int n;
    while (1) {
      n = random() % 10 + 1;
      printf("C1 sends %d\n", n);
      write(c1toc2[1], &n, sizeof(int));
      if (n == 10)
        break;

      read(c2toc1[0], &n, sizeof(int));
      printf("C1 received %d\n", n);

      if (n == 10)
        break;
    }
    exit(0);
  }
  int f2 = fork();
  if (f2 == 0) {
    srandom(getpid() * getpid());
    close(c1toc2[1]);
    close(c2toc1[0]);

    int n;
    while (1) {
      read(c1toc2[0], &n, sizeof(int));
      printf("C2 received %d\n", n);
      if (n == 10)
        break;
      n = random() % 10 + 1;
      printf("C2 sends %d\n", n);
      write(c2toc1[1], &n, sizeof(int));
      if (n == 10)
        break;
    }
    exit(0);
  }
  close(c1toc2[0]);
  close(c1toc2[1]);
  close(c2toc1[0]);
  close(c2toc1[1]);

  wait(0);
  wait(0);
  return 0;
}
