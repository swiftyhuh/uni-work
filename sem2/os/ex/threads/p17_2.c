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
  int *array;
  int n, pos;
  pthread_mutex_t *mtx;
  pthread_cond_t *cond;
} shared;

void *even(void *arg) {
  shared *sh = (shared *)arg;
  pthread_mutex_lock(sh->mtx);
  while (sh->pos % 2 != 0 && sh->pos < sh->n)
    pthread_cond_wait(sh->cond, sh->mtx);
  while (sh->pos < sh->n) {
    int num = (random() % 51) * 2;
    sh->array[sh->pos] = num;
    sh->pos++;
    pthread_cond_signal(sh->cond);
    while (sh->pos % 2 != 0 && sh->pos < sh->n)
      pthread_cond_wait(sh->cond, sh->mtx);
  }
  pthread_cond_signal(sh->cond);
  pthread_mutex_unlock(sh->mtx);
  return NULL;
}

void *odd(void *arg) {
  shared *sh = (shared *)arg;
  pthread_mutex_lock(sh->mtx);
  while (sh->pos % 2 != 1 && sh->pos < sh->n)
    pthread_cond_wait(sh->cond, sh->mtx);
  while (sh->pos < sh->n) {
    int num = (random() % 50) * 2 + 1;
    sh->array[sh->pos] = num;
    sh->pos++;
    pthread_cond_signal(sh->cond);
    while (sh->pos % 2 != 1 && sh->pos < sh->n)
      pthread_cond_wait(sh->cond, sh->mtx);
  }
  pthread_cond_signal(sh->cond);
  pthread_mutex_unlock(sh->mtx);
  return NULL;
}

int main(int argc, char *argv[]) {
  int n;
  scanf("%d", &n);

  pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(mtx, NULL);

  pthread_cond_t *cond = malloc(sizeof(pthread_cond_t));
  pthread_cond_init(cond, NULL);

  shared *sh = malloc(sizeof(shared));
  sh->n = n;
  sh->pos = 0;
  sh->array = malloc(sizeof(int) * sh->n);
  sh->mtx = mtx;
  sh->cond = cond;

  pthread_t *th = malloc(sizeof(pthread_t) * 2);

  pthread_create(&th[0], NULL, even, sh);
  pthread_create(&th[1], NULL, odd, sh);

  pthread_join(th[0], NULL);
  pthread_join(th[1], NULL);

  for (int i = 0; i < sh->n; i++)
    printf("%d \n", sh->array[i]);

  (void)argc;
  (void)argv;
  free(sh->array);
  free(sh);
  free(th);
  pthread_mutex_destroy(mtx);
  free(mtx);
  pthread_cond_destroy(cond);
  free(cond);
}
