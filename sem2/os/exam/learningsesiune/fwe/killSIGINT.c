#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <signal.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {

    printf("Exactly one argument needed!\n");

    exit(1);
  }

  int pid = atoi(argv[1]);

  kill(pid, SIGINT);

  return 0;
}
