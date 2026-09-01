// . Write a C program that receives two numbers: N and M as command-line
// arguments. The main process creates an array with exactly N integer elements,
// all with the initial value 100. The main process creates N + 1 threads. The
// first N threads will each receive one unique index IDX between 0 and N - 1
// and will execute the following loop M times:
// - Generates a random index I between 0 and N-1, different than IDX.
// - Steals a random amount (between 5% and 10%) from the array at index I and
// adds that amount to the array at position IDX.
// - Waits for all other threads to finish the current iteration of the loop.
// The last thread, before each loop iteration begins, prints the contents of
// the array, then waits for another loop iteration to complete (This thread is
// supposed to print both the initial state of the array, when all values are
// 100, as well as the final state of the array, when all other threads have
// terminated). Use efficient synchronization.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 100

int *array;
int N, M;
pthread_mutex_t mutex[MAX_THREADS];
pthread_barrier_t barrier;

void *thread_function(void *arg) {
  int idx = *(int *)arg;
  free(arg);

  for (int i = 0; i < M; i++) {
    // Generate a random index different than IDX
    int I;
    do {
      I = rand() % N;
    } while (I == idx);

    // Steal a random amount (between 5% and 10%)
    int amount = (rand() % 6 + 5) * array[I] / 100;

    // Lock the mutex for the stolen index
    pthread_mutex_lock(&mutex[I]);
    array[I] -= amount;
    pthread_mutex_unlock(&mutex[I]);

    // Lock the mutex for the current index
    pthread_mutex_lock(&mutex[idx]);
    array[idx] += amount;
    pthread_mutex_unlock(&mutex[idx]);

    // Wait for all threads to finish the current iteration
    pthread_barrier_wait(&barrier);
  }

  return NULL;
}

void *print_function(void *arg) {
  for (int i = 0; i < M; i++) {
    // Wait for all threads to reach the barrier
    pthread_barrier_wait(&barrier);

    // Print the contents of the array
    printf("Array state: ");
    for (int j = 0; j < N; j++) {
      printf("%d ", array[j]);
    }
    printf("\n");
  }
  return NULL;
}
int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s N M\n", argv[0]);
    return 1;
  }

  N = atoi(argv[1]);
  M = atoi(argv[2]);

  array = malloc(N * sizeof(int));
  for (int i = 0; i < N; i++) {
    array[i] = 100;
    pthread_mutex_init(&mutex[i], NULL);
  }

  pthread_barrier_init(&barrier, NULL, N + 1);

  pthread_t threads[N + 1];
  for (int i = 0; i < N; i++) {
    int *idx = malloc(sizeof(int));
    *idx = i;
    pthread_create(&threads[i], NULL, thread_function, idx);
  }
  pthread_create(&threads[N], NULL, print_function, NULL);

  for (int i = 0; i < N + 1; i++) {
    pthread_join(threads[i], NULL);
  }

  free(array);
  return 0;
}
