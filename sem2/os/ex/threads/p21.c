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

typedef struct {
  int n;
  sem_t *sem;
} shared;

typedef struct {
  int id;
  shared *sh;
} data;

void *checkpoint(void *arg) {
  data *d = (data *)arg;
  for (int i = 0; i < d->sh->n; i++) {
    sem_wait(&d->sh->sem[i]);
    printf("Thread %d entered checkpoint %d\n", d->id, i);
    usleep(100000);
    printf("Thread %d left checkpoint %d\n", d->id, i);
    sem_post(&d->sh->sem[i]);
    printf("\n");
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  int thCount = 1 << n;
  shared *sh = malloc(sizeof(shared));
  sem_t *s = malloc(sizeof(sem_t) * n);
  sh->sem = s;
  sh->n = n;

  pthread_t *th = malloc(sizeof(pthread_t) * thCount);

  for (int i = 0; i < n; i++)
    sem_init(&sh->sem[i], 0, 1 << (n - i - 1));

  data *d = malloc(sizeof(data) * thCount);
  for (int i = 0; i < thCount; i++) {
    d[i].id = i;
    d[i].sh = sh;
    pthread_create(&th[i], NULL, checkpoint, &d[i]);
  }

  for (int i = 0; i < thCount; i++)
    pthread_join(th[i], NULL);
  (void)argc;
  free(sh);
  free(s);
  free(d);
  free(th);
}
