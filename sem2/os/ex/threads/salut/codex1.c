//  Write a C program that creates N threads. Each thread receives an integer K
//  and a shared array of size K. Thread i writes i + 1 into position i. After
//  all positions are filled, each thread waits until every other thread has
//  written its value, then each thread prints the whole array once and
//  terminates. Use semaphores for synchronization.

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
int n, k;
int *array;
sem_t sem;
pthread_barrier_t bar;

void *f(void *arg) {
  int idx = *(int *)arg;
  sem_wait(&sem);
  array[idx] = idx + 1;
  sem_post(&sem);
  pthread_barrier_wait(&bar);
  for (int i = 0; i < n; i++)
    printf("%d \n", array[i]);
  printf("\n");
  return NULL;
}

int main(int argc, char *argv[]) {
  n = atoi(argv[1]);
  scanf("%d", &k);
  array = malloc(sizeof(int) * k);
  sem_init(&sem, 0, 1);
  pthread_barrier_init(&bar, NULL, k);
  int *idx = malloc(sizeof(int) * n);
  pthread_t *th = malloc(sizeof(pthread_t) * n);
  for (int i = 0; i < n; i++) {
    idx[i] = i;
    pthread_create(&th[i], NULL, f, &idx[i]);
  }

  for (int i = 0; i < n; i++)
    pthread_join(th[i], NULL);
}
