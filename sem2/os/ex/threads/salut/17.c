// 17. Write a C program that reads a number N and creates 2 threads. One of the
// threads will generate an even number and will append it to an array that is
// passed as a parameter to the thread. The other thread will do the same, but
// using odd numbers. Implement a synchronization between the two threads so
// that they alternate in appending numbers to the array, until they reach the
// maximum length N.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int *array;
int n, idx = 0;
pthread_mutex_t mtx;
pthread_cond_t cond;

void *even(void *arg) {
  pthread_mutex_lock(&mtx);
  while (idx < n) {
    while (idx % 2 != 0 && idx < n)
      pthread_cond_wait(&cond, &mtx);

    if (idx >= n)
      break;

    array[idx] = (rand() % 50) * 2;
    idx++;

    pthread_cond_signal(&cond);
  }
  pthread_mutex_unlock(&mtx);
  return NULL;
}

void *odd(void *arg) {
  pthread_mutex_lock(&mtx);
  while (idx < n) {
    while (idx % 2 != 1 && idx < n)
      pthread_cond_wait(&cond, &mtx);

    if (idx >= n)
      break;

    array[idx] = (rand() % 50) * 2 + 1;
    idx++;

    pthread_cond_signal(&cond);
  }
  pthread_mutex_unlock(&mtx);
  return NULL;
}

int main(int argc, char *argv[]) {
  scanf("%d", &n);
  array = malloc(sizeof(int) * n);
  pthread_mutex_init(&mtx, NULL);
  pthread_cond_init(&cond, NULL);

  pthread_t *th = malloc(sizeof(pthread_t) * 2);

  pthread_create(&th[0], NULL, even, NULL);
  pthread_create(&th[1], NULL, odd, NULL);

  pthread_join(th[0], NULL);
  pthread_join(th[1], NULL);

  printf("Array: \n");
  for (int i = 0; i < n; i++)
    printf("%d\n", array[i]);

  pthread_mutex_destroy(&mtx);
  pthread_cond_destroy(&cond);
  free(array);
  free(th);
}
