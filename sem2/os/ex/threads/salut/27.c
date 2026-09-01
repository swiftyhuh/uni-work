// 27. Write a C program that takes two numbers, N and M, as arguments from the
// command line. The program creates N "generator" threads that generate random
// lowercase letters and append them to a string with 128 positions. The program
// will create an additional "printer" thread that that waits until all the
// positions of the string are filled, at which point it prints the string and
// clears it. The N "generator" threads must generate a total of M such strings
// and the "printer" thread prints each one as soon as it gets to length 128.

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

sem_t s;
sem_t p;
pthread_mutex_t mtx;
char array[128];
int pos = 0, n, m, done = 0;

void *generator(void *arg) {
  while (1) {
    char letter = 'a' + (random() % 26);

    sem_wait(&s);
    pthread_mutex_lock(&mtx);

    if (done == m) {
      pthread_mutex_unlock(&mtx);
      sem_post(&s);
      return NULL;
    }

    array[pos] = letter;
    pos++;
    if (pos == 128)
      sem_post(&p);
    pthread_mutex_unlock(&mtx);
  }
}

void *printer(void *arg) {
  while (1) {
    sem_wait(&p);
    pthread_mutex_lock(&mtx);

    for (int i = 0; i < 128; i++)
      printf("%c", array[i]);
    printf("\n");

    done++;
    pos = 0;

    for (int i = 0; i < 128; i++)
      sem_post(&s);

    pthread_mutex_unlock(&mtx);

    if (done == m)
      return NULL;
  }
}

int main(int argc, char *argv[]) {
  n = atoi(argv[1]);
  m = atoi(argv[2]);

  srandom(time(NULL));

  pthread_mutex_init(&mtx, NULL);
  sem_init(&s, 0, 128);
  sem_init(&p, 0, 0);

  pthread_t *th = malloc(sizeof(pthread_t) * n);
  pthread_t printer_th;

  pthread_create(&printer_th, NULL, printer, NULL);

  for (int i = 0; i < n; i++)
    pthread_create(&th[i], NULL, generator, NULL);

  for (int i = 0; i < n; i++)
    pthread_join(th[i], NULL);

  pthread_join(printer_th, NULL);
}
