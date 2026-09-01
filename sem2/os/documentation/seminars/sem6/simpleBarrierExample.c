#include <pthread.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

pthread_barrier_t bar;

void *f() {

  printf("Starting\n");

  pthread_barrier_wait(&bar);

  usleep(10);

  printf("Stopping\n");

  return NULL;
}

int main() {

  // create 100 threads

  int n = 100;

  pthread_t th[n];

  // the barrier opens after 50 threads and then resets

  // change this number and see what happens

  // if the count set for the barrier divides the number of threads, the program
  // should terminate, otherwise, it will hang

  pthread_barrier_init(&bar, NULL, 50);

  for (int i = 0; i < n; i++) {

    pthread_create(&th[i], NULL, f, NULL);
  }

  for (int i = 0; i < n; i++) {

    pthread_join(th[i], NULL);
  }

  pthread_barrier_destroy(&bar);

  return 0;
}
