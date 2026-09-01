
// Execute another program received from the command line and time its execution

#include <sys/time.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/wait.h>

int main(int argc, char *argv[]) {

  struct timeval start, stop;

  gettimeofday(&start, NULL);

  int f = fork();

  if (-1 == f) {

    perror("Error on fork");

    exit(0);

  } else if (0 == f) {

    if (-1 == execvp(argv[1], argv + 1)) {

      perror("Error on execvp");
    }

    exit(0);

  } else {

    wait(0);

    gettimeofday(&stop, NULL);

    printf("Time = %lf millis\n", ((stop.tv_sec - start.tv_sec) * 1000.0 +
                                   (stop.tv_usec - start.tv_usec) / 1000.0));
  }

  return 0;
}
