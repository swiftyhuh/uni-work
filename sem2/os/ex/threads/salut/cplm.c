#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n;
int *array;
pthread_barrier_t bar;

void *f(void *arg) {
  int idx = *(int *)arg;
  array[idx] = idx + 1;

  pthread_barrier_wait(&bar);

  for (int i = 0; i < n; i++)
    printf("%d ", array[i]);
  printf("\n");

  return NULL;
}

int main(int argc, char *argv[]) {
  n = atoi(argv[1]);

  array = malloc(sizeof(int) * n);
  pthread_t *th = malloc(sizeof(pthread_t) * n);
  int *id = malloc(sizeof(int) * n);

  pthread_barrier_init(&bar, NULL, n);

  for (int i = 0; i < n; i++) {
    id[i] = i;
    pthread_create(&th[i], NULL, f, &id[i]);
  }

  for (int i = 0; i < n; i++)
    pthread_join(th[i], NULL);

  pthread_barrier_destroy(&bar);
  free(id);
  free(th);
  free(array);

  return 0;
}
