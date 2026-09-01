#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <signal.h>

int *a = NULL;

void orice(int sig) {

  printf("Received signal %d\n", sig);

  if (NULL != a) {

    free(a);

    a = NULL;
  }

  exit(0);
}

int main(int argc, char *argv[]) {

  printf("PID %d\n", getpid());

  signal(SIGINT, orice);

  a = malloc(sizeof(int));

  while (1) {

    printf("Working...\n");

    sleep(1);
  }

  return 0;
}
