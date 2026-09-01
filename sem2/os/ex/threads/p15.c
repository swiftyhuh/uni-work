// 15. Write a program that receives strings of characters as command line
// arguments. For each string the program creates a thread which calculates the
// number of digits, the number of leters and the number of special characters
// (anything other than a letter or digit). The main program waits for the
// threads to terminate and prints the total results (total number of digits,
// letters and special characters across all the received command line
// arguments) and terminates. Use efficient synchronization. Do not use global
// variables

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int idx;
  char *s;
} data;

typedef struct {
  int nDigits, nLeters, nSpecial;
} result;

void *counter(void *arg) {
  data d = *((data *)arg);
  int len = strlen(d.s);
  result *res = malloc(sizeof(result));
  res->nDigits = 0;
  res->nLeters = 0;
  res->nSpecial = 0;

  for (int i = 0; i < len; i++) {
    if ((d.s[i] >= 'A' && d.s[i] <= 'Z') || (d.s[i] >= 'a' && d.s[i] <= 'z'))
      res->nLeters += 1;
    else if (d.s[i] >= '0' && d.s[i] <= '9')
      res->nDigits += 1;
    else
      res->nSpecial += 1;
  }

  printf("Thread %d - Digits: %d | Leters: %d | Speiclas: %d\n", d.idx,
         res->nDigits, res->nLeters, res->nSpecial);
  return res;
}

int main(int argc, char *argv[]) {

  int size = argc - 1;
  pthread_t *th = malloc(sizeof(pthread_t) * size);
  data *args = malloc(sizeof(data) * size);

  for (int i = 0; i < size; i++) {
    args[i].idx = i;
    args[i].s = argv[i + 1];
    pthread_create(&th[i], NULL, counter, &args[i]);
  }

  int totalDigits = 0, totalLetters = 0, totalSpecial = 0;
  for (int i = 0; i < size; i++) {
    result *res;
    pthread_join(th[i], (void **)&res);
    totalDigits += res->nDigits;
    totalLetters += res->nLeters;
    totalSpecial += res->nSpecial;
    free(res);
  }
  printf("Total Digits: %d | Total Letters: %d | Total Specials: %d\n",
         totalDigits, totalLetters, totalSpecial);
  free(args);
  free(th);
  return 0;
}
