// 16. Write a C program that receives integers as command line argument. The
// program will keep a frequency vector for all digits. The program will create
// a thread for each argument that counts the number of occurences of each digit
// and adds the result to the frequency vector. Use efficient synchronization.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int freq[10];
  pthread_mutex_t *mtx;
} shared;

typedef struct {
  int idx;
  char *s;
  shared *sh;
} data;

void *frequency(void *arg) {
  data *d = (data *)arg;
  int len = strlen(d->s);

  for (int i = 0; i < len; i++)
    if (d->s[i] >= '0' && d->s[i] <= '9') {
      pthread_mutex_lock(d->sh->mtx);
      d->sh->freq[d->s[i] - '0']++;
      pthread_mutex_unlock(d->sh->mtx);
    }

  return NULL;
}

int main(int argc, char *argv[]) {
  int size = argc - 1;
  pthread_t *th = malloc(sizeof(pthread_t) * size);
  data *args = malloc(sizeof(data) * size);
  pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(mtx, NULL);
  shared *sh = malloc(sizeof(shared));

  for (int i = 0; i < 10; i++)
    sh->freq[i] = 0;
  sh->mtx = mtx;

  for (int i = 0; i < size; i++) {
    args[i].idx = i;
    args[i].s = argv[i + 1];
    args[i].sh = sh;
    pthread_create(&th[i], NULL, frequency, &args[i]);
  }

  for (int i = 0; i < size; i++) {
    pthread_join(th[i], NULL);
  }
  for (int i = 0; i < 10; i++)
    printf("Freq of %d : %d \n", i, sh->freq[i]);

  pthread_mutex_destroy(mtx);
  free(mtx);
  free(args);
  free(sh);
  free(th);
}
