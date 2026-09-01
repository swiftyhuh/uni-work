// 21. Write a C program that creates 2^N threads that race to the finish (N is
// a command line argument). The threads must pass through N checkpoint. The
// checkpoint with number X will allow half as many threads to pass
// simultaneously than checkpoint number X - 1 (N >= X >=1). Checkpoint 0 (the
// first one) will allow 2^(N-1) to pass simultaneously through it.

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int n;
sem_t s;
sem_t sem[100];

void *checkpoint(void *arg) {
  int idx = *(int *)arg;
  for (int i = 0; i < n; i++) {
    sem_wait(&sem[i]);
    printf("Thread %d entered checkpoint %d\n", idx, i);
    usleep(100000);
    printf("Thread %d left checkpoint %d\n", idx, i);
    sem_post(&sem[i]);
    printf("\n");
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  n = atoi(argv[1]);
  int thCount = 1 << n;

  int *ids = malloc(sizeof(int) * thCount);

  pthread_t *th = malloc(sizeof(pthread_t) * thCount);

  for (int i = 0; i < n; i++)
    sem_init(&sem[i], 0, 1 << (n - i - 1));

  for (int i = 0; i < thCount; i++) {
    ids[i] = i;
    pthread_create(&th[i], NULL, checkpoint, &ids[i]);
  }

  for (int i = 0; i < thCount; i++)
    pthread_join(th[i], NULL);

  free(th);
}
