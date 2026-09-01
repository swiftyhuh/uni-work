// Create N threads, each thread generates some treasure on start up. After all
// threads have generated their treasure, each thread will randomly select
// another thread's treasure and steal 10% from it.

#include <stdio.h>

#include <stdlib.h>

#include <error.h>

#include <errno.h>

#include <unistd.h>

#include <pthread.h>

typedef struct {

  int value;

  pthread_mutex_t *m;

} treasure;

typedef struct {

  int id;

  int n;

  pthread_barrier_t *b;

  treasure *t;

} data;

void *f(void *arg) {

  data d = *((data *)arg);

  int value = rand() % 1000;

  printf("Thread %d generated treasure %d\n", d.id, value);

  d.t[d.id].value = value;

  pthread_barrier_wait(d.b);

  int sleep_time = rand() % 100 + 100;

  usleep(sleep_time * 1000);

  int index = rand() % d.n;

  while (index == d.id) {

    index = rand() % d.n;
  }

  int stolen;

  pthread_mutex_lock(d.t[index].m);

  stolen = d.t[index].value / 10;

  d.t[index].value -= stolen;

  pthread_mutex_unlock(d.t[index].m);

  printf("Thread %d stole %d from thread %d\n", d.id, stolen, index);

  pthread_mutex_lock(d.t[d.id].m);

  d.t[d.id].value += stolen;

  pthread_mutex_unlock(d.t[d.id].m);

  return NULL;
}

int main(int argc, char *argv[]) {

  if (argc != 2) {

    printf("Please provide one argument\n");

    exit(1);
  }

  int n = atoi(argv[1]);

  srand(getpid());

  pthread_t *th = malloc(sizeof(pthread_t) * n);

  data *args = malloc(sizeof(data) * n);

  treasure *t = malloc(sizeof(treasure) * n);

  pthread_mutex_t *m = malloc(sizeof(pthread_mutex_t) * n);

  pthread_barrier_t *b = malloc(sizeof(pthread_barrier_t));

  pthread_barrier_init(b, NULL, n);

  for (int i = 0; i < n; i++) {

    pthread_mutex_init(&m[i], NULL);

    t[i].m = &m[i];

    args[i].id = i;

    args[i].n = n;

    args[i].t = t;

    args[i].b = b;
  }

  for (int i = 0; i < n; i++) {

    if (0 != pthread_create(&th[i], NULL, f, &args[i])) {

      error(0, errno, "Cannot start thread %d", i);

      break;
    }
  }

  for (int i = 0; i < n; i++) {

    pthread_join(th[i], NULL);
  }

  for (int i = 0; i < n; i++) {

    pthread_mutex_destroy(&m[i]);
  }

  for (int i = 0; i < n; i++) {

    printf("Treasure %d -> value %d\n", i, t[i].value);
  }

  pthread_barrier_destroy(b);

  free(t);

  free(args);

  free(m);

  free(b);

  free(th);

  return 0;
}
