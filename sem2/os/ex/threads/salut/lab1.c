// Write a C program that receives N command-line arguments. For each argument,
// the␍ main process creates a thread. Each thread will check if its argument is
// a regular file␍ and, if yes, it will print its size in bytes and add that
// amount to a total. If the argument is␍ not a regular file, the thread will
// print a corresponding message and terminate. After all␍ threads terminate,
// the main process will print the total. Use efficient synchronization.␍
// Notes:␍
//- Use stat to obtain the file type and size of the file in bytes:␍
//- st_mode holds the file type␍
//- st_size holds the file size␍
//- See man 2 stat (contains code example) and man 3 stat for more details␍
// struct stat sb;␍
// stat(filename, &sb);␍
// if ((sb.st_mode & S_IFMT) == S_IFREG) {␍
//  it is a regular file␍
// }

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

pthread_mutex_t mtx;
int total = 0;

void *f(void *arg) {
  struct stat sb;
  char *a = (char *)arg;
  if (stat(a, &sb) != 0) {
    printf("Nu e bon boss\n");
    return NULL;
  }
  if ((sb.st_mode & S_IFMT) == S_IFREG) {
    pthread_mutex_lock(&mtx);
    total += sb.st_size;
    printf("Size: %jd \n", sb.st_size);
    pthread_mutex_unlock(&mtx);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  int thCount = argc - 1;
  pthread_t *th = malloc(sizeof(pthread_t) * thCount);
  pthread_mutex_init(&mtx, NULL);

  for (int i = 0; i < thCount; i++)
    pthread_create(&th[i], NULL, f, argv[i + 1]);

  for (int i = 0; i < thCount; i++)
    pthread_join(th[i], NULL);

  printf("Total: %d\n", total);
  free(th);
  pthread_mutex_destroy(&mtx);
}
