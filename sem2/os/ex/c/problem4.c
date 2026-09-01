#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct timeval tv1, tv2;

  if (argc < 2) {
    printf("Please provide at least one argument.\n");
    exit(1);
  }
  gettimeofday(&tv1, NULL);
  int f = fork();
  if (f == -1) {
    perror("Error on fork");
    exit(1);
  }

  if (f == 0) {
    execvp(argv[1], argv + 1);
    perror("Error running command");
    exit(1);
  } else {
    wait(0);
    gettimeofday(&tv2, NULL);
    double total =
        ((tv2.tv_usec - tv1.tv_usec) / 1000000) + tv2.tv_sec - tv1.tv_sec;
    printf("Total time = %f", total);
  }

  return 0;
}
