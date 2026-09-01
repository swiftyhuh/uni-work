#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <string.h>

typedef struct {

  char arr[8];

  unsigned long long k;

} whatever;

void *f(void *arg) {

  whatever b = *((whatever *)arg);

  printf("This thread has received a %s of size %llu\n", b.arr, b.k);

  int *ret = malloc(sizeof(int));

  *ret = 1000;

  return ret;
}

int main(int argc, char *argv[]) {

  // when creating a thread, the thread function takes a void * argument

  // void * is C's way of saying that it can be a pointer to anything

  // so for this example, we'll send a structure containing a string of maximum
  // 8 characters and an unsigned long long, but we could send pretty much
  // whatever we'd like - within reason

  whatever b;

  strcpy(b.arr, "banana");

  b.k = 3;

  pthread_t th;

  // pthread_create will create and start a thread

  // the thread starts by executing the given function with an argument (3rd and
  // 4th arguments)

  pthread_create(&th, NULL, f, &b); // the thread does something like f(&b)

  // the thread function also returns void *

  // obtaining whatever the function returns can be done as follows

  // - the thread must allocate space on the heap to store its result

  // - the thread returns the pointer (address) to that heap location

  // in the main process, declare a pointer of the same type as the type
  // returned from the thread function (in this example we return an int, but
  // replace int with whatever data type you need, both here and in the thread
  // function)

  // - the main process does not need to allocate space for the result, since
  // all it need is the address returned from the thread

  // - this pointer is passed as an OUT parameter to pthread_join, as such, we
  // must pass a reference to it (address)

  // thus, the infamous "we need the address of the pointer variable" is spawned

  int *i;

  pthread_join(th, (void **)&i);

  printf("From the thread we received: %d\n", *i);

  // finally, the main process must deallocate the memory that was allocated in
  // the thread

  free(i);

  return 0;
}
