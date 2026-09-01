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

void *my_thread_function(void *thread_arg) {
  sover st = *((sover *)thread_arg);
  // int *nr;
  printf("Thread %d started\n", st.idx);
  for (int i = 0; i < 1000000; i++) {
    pthread_mutex_lock(st.mtx);
    nr++;
    pthread_mutex_unlock(st.mtx);
  }

  return NULL;
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
    pthread_join(th[i], NULL);
  }

  free(args);
  printf("the nr is %d\n", nr);
  return 0;
}
