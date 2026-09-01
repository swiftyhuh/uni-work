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

pthread_mutex_t mtx;
int nDigit = 0, nLetter = 0, nSpecial = 0;
char **s;
void *f(void *arg) {
  char *s = (char *)arg;
  int len = strlen(s);
  for (int i = 0; i < len; i++)
    if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')) {
      pthread_mutex_lock(&mtx);
      nLetter++;
      pthread_mutex_unlock(&mtx);
    } else if (s[i] >= '0' && s[i] <= '9') {
      pthread_mutex_lock(&mtx);
      nDigit++;
      pthread_mutex_unlock(&mtx);
    } else {
      pthread_mutex_lock(&mtx);
      nSpecial++;
      pthread_mutex_unlock(&mtx);
    }
  return NULL;
}

int main(int argc, char *argv[]) {
  int n = argc - 1;
  pthread_t *th = malloc(sizeof(pthread_t) * n);

  s = argv + 1;
  for (int i = 0; i < n; i++) {
    pthread_create(&th[i], NULL, f, s[i]);
  }

  for (int i = 0; i < n; i++)
    pthread_join(th[i], NULL);

  printf("Total digits: %d | Total letter: %d | Total Special: %d\n", nDigit,
         nLetter, nSpecial);
}
