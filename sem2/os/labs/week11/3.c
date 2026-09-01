#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// protect criticla sections in code, nothing else, don t mutex if its not
// needed
int nr = 0;

typedef struct {
  int idx;
  int my_number;
  pthread_mutex_t *mtx;
} sover; // any name

typedef struct {
  int x;
  char str;
} dummy;

void *my_thread_function(void *thread_arg) {
  sover st = *((sover *)thread_arg);
  // int *nr;
  printf("Thread %d started\n", st.idx);
  for (int i = 0; i < 1000000; i++) {
    pthread_mutex_lock(st.mtx);
    nr++;
    pthread_mutex_unlock(st.mtx);
  }
  dummy *result = malloc(sizeof(dummy));
  result->x = st.idx;
  result->str = random() % 26 + 'a';
  // if the struct its a pointer you can acces with -> or with .x if you marked
  // it as a pointer
  return result;
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Please provide a number of threads to create\n");
    exit(1);
  }

  int thrd_count = atoi(argv[1]);
  pthread_mutex_t mtx;
  pthread_mutex_init(&mtx, NULL);
  pthread_t *th = malloc(sizeof(pthread_t) * thrd_count);
  sover *args = malloc(sizeof(sover) * thrd_count);

  for (int i = 0; i < thrd_count; i++) {
    args[i].idx = i;
    args[i].my_number = random() % 100;
    args[i].mtx = &mtx;
    pthread_create(&th[i], NULL, my_thread_function, &args[i]);
  }

  for (int i = 0; i < thrd_count; i++) {
    dummy *d;
    pthread_join(th[i], (void **)&d);
    printf("Thread %d terminated an got letter %c\n", d->x, d->str);
    free(d);
  }

  free(args);
  free(th);
  printf("the nr is %d\n", nr);
  return 0;
}

// expect one-2 thread problems, it will contian treads, mutex, barriers);
