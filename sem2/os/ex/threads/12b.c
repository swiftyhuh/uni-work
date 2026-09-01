// 12a. Write a C s a matrix of integers from a file. It then creates as many
// threads as there are rows in the matrix, each thread calculates the sum of
// the numbers on a row. The main process waits for the threads to finish, then
// prints the sums.
//
// 12b. Same as 12a, but calculate the sum of all the elements of the matrix
// using as many threads as there are rows, each thread adds to the total the
// numbers on a row. Use the test matrix to check if the program is calculating
// the total sum correctly. The expected result is 1000000. Try with and without
// mutex.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int totalSum;
  pthread_mutex_t *mtx;
} shared;

typedef struct {
  int row, cols, **matrix;
  shared *sh;
} data;

void *compute(void *arg) {
  data d = *((data *)arg);
  int localSum = 0;
  for (int i = 0; i < d.cols; i++)
    localSum += d.matrix[d.row][i];

  pthread_mutex_lock(d.sh->mtx);
  d.sh->totalSum += localSum;
  pthread_mutex_unlock(d.sh->mtx);

  return NULL;
}

int main(int argc, char *argv[]) {
  (void)argc;
  FILE *file;
  file = fopen(argv[1], "r");

  int rows, cols;
  fscanf(file, "%d %d", &rows, &cols);

  int **matrix = malloc(sizeof(int *) * rows);
  for (int i = 0; i < rows; i++)
    matrix[i] = malloc(sizeof(int) * cols);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      fscanf(file, "%d", &matrix[i][j]);

  // for (int i = 0; i < rows; i++) {
  //   for (int j = 0; j < cols; j++)
  //     printf("%d ", matrix[i][j]);
  //   printf("\n");
  // }

  pthread_t *th = malloc(sizeof(pthread_t) * rows);
  pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(mtx, NULL);

  shared *sh = malloc(sizeof(shared) * rows);
  sh->totalSum = 0;
  sh->mtx = mtx;

  data *args = malloc(sizeof(data) * rows);

  for (int i = 0; i < rows; i++) {
    args[i].row = i;
    args[i].cols = cols;
    args[i].matrix = matrix;
    args[i].sh = sh;
    pthread_create(&th[i], NULL, compute, &args[i]);
  }

  for (int i = 0; i < rows; i++)
    pthread_join(th[i], NULL);

  printf("%d\n", sh->totalSum);

  for (int i = 0; i < rows; i++)
    free(matrix[i]);

  pthread_mutex_destroy(mtx);
  free(th);
  free(sh);
  free(args);
  free(mtx);
  free(matrix);
  fclose(file);
}
