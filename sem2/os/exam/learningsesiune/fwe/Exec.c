// Execute bash commands

// - firstly by hardcoding them

// - then take them directly from the command line

#include <unistd.h>

#include <stdio.h>

int main(int argc, char *argv[]) {

  // exec functions, if successfull, overwrite the current process

  // so if you want to test one of the execs below, comment out the ones above
  // it

  // execl and execlp are variadic functions (can take a variable number of
  // arguments)

  printf("Running execl\n");

  if (-1 == execl("/usr/bin/ls", "/usr/bin/ls", "-l", "-a", NULL)) {

    perror("Error on execl");
  }

  printf("Done with execl\n");

  printf("Running execlp\n");

  if (-1 == execlp("ls", "ls", "-l", "-a", NULL)) {

    perror("Error on execlp");
  }

  printf("Done with execlp\n");

  // execv and execvp take an array of strings as arguments

  // the array must obey the same rules as argv (first element must be the
  // command itself, last element must be NULL) so we can actually pass argv to
  // execv

  // here, we want to run

  // ./exe cmd arg1 arg2 ...

  // since argv[0] = "./exe", we'll skip it and pass the array starting with
  // position 1, which can be done in a few ways: &argv[1] or argv + 1 being two
  // examples

  printf("Running execv\n");

  if (-1 == execv(argv[1], &argv[1])) {

    perror("Error on execv");
  }

  printf("Done with execv\n");

  printf("Running execvp\n");

  if (-1 == execvp(argv[1], argv + 1)) {

    perror("Error on execvp");
  }

  return 0;
}
