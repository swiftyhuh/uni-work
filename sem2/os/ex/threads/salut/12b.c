// 12a. Write a C program that reads a matrix of integers from a file. It then
// creates as many threads as there are rows in the matrix, each thread
// calculates the sum of the numbers on a row. The main process waits for the
// threads to finish, then prints the sums.
//  12b. Same as 12a, but calculate the sum of all the elements of the matrix
//  using as many threads as there are rows, each thread adds to the total the
//  numbers on a row. Use the test matrix to check if the program is calculating
//  the total sum correctly. The expected result is 1000000. Try with and
//  without mutex.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int **matrix;
int n, m, total;
pthread_mutex_t mtx;

void *f(void *arg) {
  int row = *(int *)arg;
  int sum = 0;

  for (int i = 0; i < m; i++)
    sum += matrix[row][i];

  pthread_mutex_lock(&mtx);
  total += sum;
  pthread_mutex_unlock(&mtx);
  return NULL;
}

int main(int argc, char *argv[]) {
  FILE *file;
  file = fopen(argv[1], "r");

  fscanf(file, "%d %d", &n, &m);

  matrix = malloc(sizeof(int *) * n);
  for (int i = 0; i < n; i++)
    matrix[i] = malloc(sizeof(int) * m);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      fscanf(file, " %d", &matrix[i][j]);

  fclose(file);

  pthread_t *th = malloc(sizeof(pthread_t) * n);
  int *rows = malloc(sizeof(int) * n);

  total = 0;
  pthread_mutex_init(&mtx, NULL);

  for (int i = 0; i < n; i++) {
    rows[i] = i;
    pthread_create(&th[i], NULL, f, &rows[i]);
  }

  for (int i = 0; i < n; i++)
    pthread_join(th[i], NULL);

  printf("%d\n", total);

  pthread_mutex_destroy(&mtx);
  free(rows);
  free(th);
}
