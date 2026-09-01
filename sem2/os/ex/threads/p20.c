// 20. Write a C program that takes as command line arguments 2 numbers: N and
// M. The program will simulate a thread race that have to pass through M
// checkpoints. Through each checkpoint the threads must pass one at a time (no
// 2 threads can be inside the same checkpoint). Each thread that enters a
// checkpoint will wait between 100 and 200 milliseconds (usleep(100000) makes a
// thread or process wait for 100 milliseconds) and will print a message
// indicating the thread number and the checkpoint number, then it will exit the
// checkpoint. Ensure that no thread will try to pass through a checkpoint until
// all threads have been created.

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Please provide 2 numbers: N and M\n");
    exit(0);
  }

  int n, m;
  n = atoi(argv[1]);
  m = atoi(argv[2]);
  printf("Testing: N = %d, M = %d\n", n, m);
}
