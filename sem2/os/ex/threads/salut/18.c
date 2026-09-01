// 18. Create a C program that converts all lowecase letters from the command
// line arguments to uppercase letters and prints the result. Use a thread for
// each given argument.

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sem_t sem;
pthread_barrier_t bar;
char **in;
int size;

void *f(void *arg) {
  char *s = (char *)arg;
  int len = strlen(s);
  for (int i = 0; i < len; i++)
    if (s[i] >= 'a' && s[i] <= 'z') {
      sem_wait(&sem);
      s[i] = s[i] - 'a' + 'A';
      sem_post(&sem);
    }
  pthread_barrier_wait(&bar);
  for (int i = 0; i < size; i++)
    printf("%s ", in[i]);
  return NULL;
}
int main(int argc, char *argv[]) {
  in = argv + 1;
  size = argc - 1;
  pthread_t *th = malloc(sizeof(pthread_t) * size);
  pthread_barrier_init(&bar, NULL, size);
  sem_init(&sem, 0, 1);
  for (int i = 0; i < size; i++) {
    pthread_create(&th[i], NULL, f, argv[i + 1]);
  }

  for (int i = 0; i < size; i++)
    pthread_join(th[i], NULL);

  free(th);
  pthread_barrier_destroy(&bar);
  sem_destroy(&sem);
}
