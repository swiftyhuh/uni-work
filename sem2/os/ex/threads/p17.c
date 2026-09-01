// 17. Write a C program that reads a number N and creates 2 threads. One of the
// threads will generate an even number and will append it to an array that is
// passed as a parameter to the thread. The other thread will do the same, but
// using odd numbers. Implement a synchronization between the two threads so
// that they alternate in appending numbers to the array, until they reach the
// maximum length N.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int *v;
  int n, pos, turn;
  pthread_mutex_t *mtx;
} shared;

void *even(void *arg) {
  srand(6);
  shared *e = (shared *)arg;
  if (e->pos == e->n)
    return NULL;
  int x = random();
  if (x % 2 == 1)
    x += 1;
  pthread_mutex_lock(e->mtx);
  e->v[e->pos] = x;
  e->pos++;
  pthread_mutex_unlock(e->mtx);
  return NULL;
}

void *odd(void *arg) {
  srand(9);
  shared *o = (shared *)arg;
  if (o->pos == o->n)
    return NULL;
  int x = random();
  if (x % 2 == 0)
    x += 1;
  o->v[o->pos] = x;
  o->pos++;
  return NULL;
}

int main(int argc, char *argv[]) {
  shared *e = malloc(sizeof(shared));
  pthread_t *th = malloc(sizeof(pthread_t) * 2);
  e->pos = 0;
  e->n = atoi(argv[1]);
  e->v = malloc(sizeof(int) * e->n);

  pthread_mutex_t mtx;
  pthread_mutex_init(&mtx, NULL);

  while (e->pos < e->n) {
    e->mtx = &mtx;
    pthread_create(&th[0], NULL, even, e);
    pthread_create(&th[1], NULL, odd, e);
  }
  pthread_join(th[0], NULL);
  pthread_join(th[1], NULL);

  for (int i = 0; i < e->n; i++) {
    printf("Pos: %d | value: %d \n", i, e->v[i]);
  }
  free(e);
  free(th);
  pthread_mutex_destroy(&mtx);
  (void)argc;
}
