#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int *arr, N, idx = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *f1(void *arg) {
  int i;
  pthread_mutex_lock(&mutex);
  if (idx % 2 != 0)
    pthread_cond_wait(&cond, &mutex);
  while (idx < N) {
    int num = (random() % 51) * 2;
    arr[idx] = num;
    idx += 1;
    printf("T1: ");
    for (i = 0; i < idx; i++) {
      printf("%d ", arr[i]);
    }
    printf("\n");

    pthread_cond_signal(&cond);
    if (idx % 2 != 0)
      pthread_cond_wait(&cond, &mutex);
  }
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void *f2(void *arg) {
  int i;
  pthread_mutex_lock(&mutex);
  if (idx % 2 != 1)
    pthread_cond_wait(&cond, &mutex);
  while (idx < N) {
    int num = (random() % 50) * 2 + 1;
    arr[idx] = num;
    idx += 1;
    printf("T2: ");
    for (i = 0; i < idx; i++) {
      printf("%d ", arr[i]);
    }
    printf("\n");

    pthread_cond_signal(&cond);
    if (idx % 2 != 1)
      pthread_cond_wait(&cond, &mutex);
  }
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Please provide one command line argument!\n");
    exit(1);
  }
  N = atoi(argv[1]);
  srandom(time(NULL));
  arr = malloc(sizeof(int) * N);
  pthread_t T[2];
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
  pthread_create(&T[0], NULL, f1, NULL);
  pthread_create(&T[1], NULL, f2, NULL);

  pthread_join(T[0], NULL);
  pthread_join(T[1], NULL);
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  free(arr);
  return 0;
}
