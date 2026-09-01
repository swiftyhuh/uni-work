#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <threads.h>

typedef struct {
  int total, n;
  pthread_mutex_t *mtx;
} shared;

typedef struct {
  char *a;
  shared *sh;
} data;

void *salut(void *arg) {
  struct stat sb;
  data *d = (data *)arg;
  stat(d->a, &sb);
  if ((sb.st_mode & S_IFMT) == S_IFREG) {
    pthread_mutex_lock(d->sh->mtx);
    d->sh->total += sb.st_size;
    printf("Size: %jd \n", sb.st_size);
    pthread_mutex_unlock(d->sh->mtx);
  } else {
    printf("Nu e bun boss \n");
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  int thCount = argc - 1;
  pthread_t *th = malloc(sizeof(pthread_t) * thCount);
  data *d = malloc(sizeof(data) * thCount);
  pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(mtx, NULL);
  shared *sh = malloc(sizeof(shared));

  sh->total = 0;
  sh->n = thCount;
  sh->mtx = mtx;
  for (int i = 0; i < thCount; i++) {
    d[i].a = argv[i + 1];
    d[i].sh = sh;
    pthread_create(&th[i], NULL, salut, &d[i]);
  }
  for (int i = 0; i < thCount; i++)
    pthread_join(th[i], NULL);
  printf("Total size: %d \n", sh->total);
  pthread_mutex_destroy(mtx);
  free(th);
  free(d);
  free(sh);
  free(mtx);
}
