#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_barrier_t bar;

void *thread(void *argc) {
  (void)argc;
  printf("Before\n");
  pthread_barrier_wait(&bar);
  printf("After\n");
  pthread_barrier_wait(&bar);
  printf("After 2\n");
  return NULL;
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  pthread_barrier_init(&bar, NULL, 10);
  pthread_t th[10];
  for (int i = 0; i < 10; i++)
    pthread_create(&th[i], NULL, thread, NULL);
  for (int i = 0; i < 10; i++)
    pthread_join(th[i], NULL);

  pthread_barrier_destroy(&bar);
  return 0;
}
