#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int idx;
  int my_number;
} sover; // any name

void *my_thread_function(void *thread_arg) {
  sover st = *((sover *)thread_arg);
  printf("Thread %d has number: %d\n", st.idx, st.my_number);
  return NULL;
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Please provide a number of threads to create\n");
    exit(1);
  }

  int thrd_count = atoi(argv[1]);
  pthread_t *th = malloc(sizeof(pthread_t) * thrd_count);
  sover *args = malloc(sizeof(sover) * thrd_count);

  for (int i = 0; i < thrd_count; i++) {
    args[i].idx = i;
    args[i].my_number = random() % 100;
    pthread_create(&th[i], NULL, my_thread_function, &args[i]);
  }

  for (int i = 0; i < thrd_count; i++) {
    pthread_join(th[i], NULL);
  }

  free(args);
  return 0;
}
