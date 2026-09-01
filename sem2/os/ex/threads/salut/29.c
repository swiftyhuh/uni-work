// 29. Write a C program that reads a number n from standard input and creates n
// threads, numbered from 0 to n - 1. Each thread places a random number between
// 10 and 20 on the position indicated by its id in an array of integers. After
// all threads have placed their number in the array, each thread repeats the
// following:
//- Checks if the number on its own position is greater than 0.
//- If yes, it substracts 1 from all numbers of the array, except the one on its
//own position.
//- If not, the thread terminates.
//- If there are no numbers in the array that are greater than 0, except the
//number on the thread's index position, the thread terminates. After all
// threads terminate, the main process prints the array of integers. Use
// appropriate synchronization mechanisms. Scrieti un program C care citeste un
// numar n de la tastatura si apoi creeaza n thread-uri numerotate de la 0 la n
// - 1. Fiecare thread pune un numar aleator intre 10 si 20 pe pozitia indicata
// de indexul sau intr-un sir de intregi. Dupa ce toate thread-urile au adaugat
// numarul in sir, fiecare thread repeta urmatorii pasi:
//- Verifica daca numarul din sir de pe indexul sau este mai mare ca 0.
//- Daca da, scade 1 din toate numerele din sir exceptand numarul de pe pozitia
//sa.
//- Daca nu, isi incheie executia.
//- Daca nu mai exista numere mai mari ca 0 in sir, exceptand numarul de pe
//pozitia sa, atunci isi incheie executia. Dupa ce toate thread-urile isi
// incheie executia, procesul principal afiseaza sirul de numere. Folositi
// mecanisme de sincronizare corespunzatoare. solution

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n;
pthread_barrier_t bar;
pthread_mutex_t mtx;
int *array;

void *f(void *arg) {
  int idx = *(int *)arg;
  int number = random() % (20 - 10 + 1) + 10;
  array[idx] = number;

  pthread_barrier_wait(&bar);
  while (1) {
    pthread_mutex_lock(&mtx);

    if (array[idx] <= 0) {
      pthread_mutex_unlock(&mtx);
      return NULL;
    }
    int ok = 0;
    for (int i = 0; i < n; i++)
      if (i != idx && array[i] > 0) {
        ok = 1;
        break;
      }
    if (!ok) {
      pthread_mutex_unlock(&mtx);
      return NULL;
    }
    for (int i = 0; i < n; i++)
      if (i != idx)
        array[i]--;
    pthread_mutex_unlock(&mtx);
  }
}

int main(int argc, char *argv[]) {
  scanf("%d", &n);
  pthread_t *th = malloc(sizeof(pthread_t) * n);
  array = malloc(sizeof(int) * n);
  pthread_barrier_init(&bar, NULL, n);
  pthread_mutex_init(&mtx, NULL);
  int *id = malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    id[i] = i;
    pthread_create(&th[i], NULL, f, &id[i]);
  }

  for (int i = 0; i < n; i++)
    pthread_join(th[i], NULL);

  for (int i = 0; i < n; i++)
    printf(" array[%d] | %d ,", i, array[i]);
  printf("\n");
  free(id);
  free(th);
  free(array);
  pthread_barrier_destroy(&bar);
  pthread_mutex_destroy(&mtx);
}
