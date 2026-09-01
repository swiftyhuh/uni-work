// 16. Write a C program that receives integers as command line argument. The
// program will keep a frequency vector for all digits. The program will create
// a thread for each argument that counts the number of occurences of each digit
// and adds the result to the frequency vector. Use efficient synchronization.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  int idx;
  char *s;
} data;

typedef struct {
  int freq[10];
} result;

void *frequency(void *arg) {
  data d = *((data *)arg);
  int len = strlen(d.s);
  result *res = malloc(sizeof(result));
  for (int i = 0; i < 10; i++)
    res->freq[i] = 0;

  for (int i = 0; i < len; i++)
    if (d.s[i] >= '0' && d.s[i] <= '9')
      res->freq[d.s[i] - '0']++;

  return res;
}

int main(int argc, char *argv[]) {
  int size = argc - 1;
  pthread_t *th = malloc(sizeof(pthread_t) * size);
  data *args = malloc(sizeof(data) * size);

  for (int i = 0; i < size; i++) {
    args[i].idx = i;
    args[i].s = argv[i + 1];
    pthread_create(&th[i], NULL, frequency, &args[i]);
  }

  int totalFreq[10] = {0};

  for (int i = 0; i < size; i++) {
    result *res;
    pthread_join(th[i], (void **)&res);
    for (int j = 0; j < 10; j++)
      totalFreq[j] += res->freq[j];
    free(res);
  }
  for (int i = 0; i < 10; i++)
    printf("Freq of %d : %d \n", i, totalFreq[i]);

  free(args);
  free(th);
}
