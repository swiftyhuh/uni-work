1. Write a C program that creates n child
    processes.Each child process will print its PID and its parent
        PID.The parent process will print its PID and the PID of each of the
            child processes.solution :
#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>

    int main(int argc, char *argv[]) {

  if (argc != 2) {

    perror("Please provide exactly one argument");

    exit(1);
  }

  int n = atoi(argv[1]);

  for (int i = 0; i < n; i++) {

    int f = fork();

    if (-1 == f) {

      perror("Error on fork");

    } else if (0 == f) {

      printf("Child process %d - PID: %d - PPID: %d\n", i, getpid(), getppid());

      exit(0);

    } else {

      printf("Parent %d - Child: %d\n", getpid(), f);
    }
  }

  for (int i = 0; i < n; i++) {

    wait(NULL);
  }

  return 0;
}

2. Write a C program that creates a linear hierarchy of n
processes(a parent process creates a child process,
          which in turn creates a child process, and so on)
    .iterative solution :
#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>

    int main(int argc, char *argv[]) {

  if (argc != 2) {

    perror("Please provide exactly one argument");

    exit(1);
  }

  int n = atoi(argv[1]);

  for (int i = 0; i < n; i++) {

    int f = fork();

    if (-1 == f) {

      perror("Error on fork");

    } else if (0 == f) {

      printf("Child process %d - PID: %d - PPID: %d\n", i, getpid(), getppid());

    } else {

      printf("Parent %d - Child: %d\n", getpid(), f);

      wait(0);

      exit(0);
    }
  }

  return 0;
}
recursive soltuion :
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
    void f(int n) {
  if (n > 0) {
    int k = fork();
    if (k < 0) {
      perror("Error on fork");
      exit(1);
    } else if (k == 0) {
      printf("PID=%d - PPID=%d\n", getpid(), getppid());
      f(n - 1);
    }
  }
  wait(0);
  exit(0);
}

int main(int argc, char **argv) {
  f(3);
  return 0;
}

3. Write a C program that creates a child process. Both the parent and the child processes will run until they receive a SIGUSR1 signal. Implement signal handling such that if the parent receives the SIGUSR1 signal first, it sends it to the child process as well. If the child process receives a SIGUSR1 signal without the parent receiving the same signal, it will terminate and then the parent should correctly call wait for the child process.
soltuion:

/*

 * Create a child process.

 * Both the child and parent processes will "work" an indefinite amount of time.

 * Implement a mechanism such that when the parent terminates, the child process
 also terminates without creating zombie processes.

 */

#include <stdlib.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <stdio.h>

#include <unistd.h>

int f;

void child_handler(int sig) {

  // if the child is the one terminating first, simply print a message and end

  printf("Child process terminating...\n");

  exit(0);
}

void parent_handler(int sig) {

  // if the parent is the one terminating first, send a SIGUSR1 to the child to
  // force its termination also

  printf("Parent process terminating...\n");

  // kill and wait are signal-safe (as per man 7 signal-safety) so they can be
  // used in a signal handler

  kill(f, SIGUSR1);

  wait(0);

  exit(0);
}

void zombie_handler(int sig) {

  // if the child terminates before the parent process, ensure that the PID is
  // released

  printf("Parent waiting for child process to terminate\n");

  wait(0);
}

int main(int argc, char **argv) {

  f = fork();

  if (-1 == f) {

    perror("Error on fork");

  } else if (0 == f) {

    signal(SIGUSR1, child_handler);

    printf("C - Child PID: %d Parent PID: %d\n", getpid(), getppid());

    while (1) {

      printf("Child working...\n");

      sleep(3);
    }

    exit(0);

  } else {

    signal(SIGUSR1, parent_handler);

    signal(SIGCHLD, zombie_handler);

    printf("P - Child PID: %d Parent PID: %d\n", f, getpid());

    while (1) {

      printf("Parent working...\n");

      sleep(2);
    }
  }

  return 0;
}

4. Write a C program that runs a bash command(potentially with arguments)
    received as a command line argument and times its execution.solution :
/* Create a C program that runs a bash command received as a command line
 * argument and prints its execution time. Ex:
 * ./exe grep -E -c "^[a-z]{4}[0-9]{4}" /etc/passwd
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
    int main(int argc, char *argv[]) {
  struct timeval tv1, tv2;
  if (argc < 2) {
    printf("Please provide at least one argument.\n");
    exit(1);
  }
  gettimeofday(&tv1, NULL);
  int f = fork();
  if (-1 == f) {
    perror("Error on fork: ");
    exit(1);
  } else if (0 == f) {
    if (-1 == execvp(argv[1], argv + 1)) {
      perror("Error running the given command: ");
      exit(1);
    }
  } else {
    wait(0);
    gettimeofday(&tv2, NULL);
    printf("Total time = %f seconds\n",
           (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
               (double)(tv2.tv_sec - tv1.tv_sec));
  }
  return 0;
}

6. Create a C program that generates N random
integers(N given at the command line)
    .It then creates a child,
    sends the numbers via pipe
        .The child calculates the average and sends the result back.soltuion :
/* Create a C program that generates N random integers (N given at the command
 * line). It then creates a child, sends the numbers via pipe. The child
 * calculates the average and sends the result back.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

    int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Please provide exactly one argument.\n");
    exit(1);
  }
  int p_to_c[2], c_to_p[2];
  pipe(p_to_c);
  pipe(c_to_p);
  int f = fork();
  if (-1 == f) {
    perror("Error on fork ");
    exit(1);
  } else if (0 == f) {
    // close unused pipe ends
    close(p_to_c[1]);
    close(c_to_p[0]);
    int n = 0, i, nr;
    float rez = 0;
    if (0 > read(p_to_c[0], &n, sizeof(int))) {
      perror("Error on read n from parent ");
      close(p_to_c[0]);
      close(c_to_p[1]);
      exit(1);
    }
    for (i = 0; i < n; i++) {
      if (0 > read(p_to_c[0], &nr, sizeof(int))) {
        perror("Error on read from parent ");
        close(p_to_c[0]);
        close(c_to_p[1]);
        exit(1);
      }
      rez += nr;
    }
    rez /= n;
    if (0 > write(c_to_p[1], &rez, sizeof(float))) {
      perror("Error on write result to parent ");
      close(p_to_c[0]);
      close(c_to_p[1]);
      exit(1);
    }
    close(p_to_c[0]);
    close(c_to_p[1]);
    exit(0);
  } else {
    // close unused pipe ends
    close(p_to_c[0]);
    close(c_to_p[1]);
    // convert the parameter from string to int
    int n = atoi(argv[1]);
    int i, nr;
    float rez = -1;
    // init random seed to prevent random from returning the same series
    srandom(time(0));
    // send n first
    if (0 > write(p_to_c[1], &n, sizeof(int))) {
      perror("Error on write n to child ");
      close(p_to_c[1]);
      close(c_to_p[0]);
      wait(0);
      exit(1);
    }
    // then send n integers
    for (i = 0; i < n; i++) {
      // limit the number generation between 0 and 99 just so we can easily
      // check that the calculation is correct
      nr = random() % 100;
      printf("Parent generated %d\n", nr);
      if (0 > write(p_to_c[1], &nr, sizeof(int))) {
        perror("Error on write number to child ");
        close(p_to_c[1]);
        close(c_to_p[0]);
      }
    }
    wait(0);
    if (0 > read(c_to_p[0], &rez, sizeof(float))) {
      perror("Error on read result from child ");
    }
    printf("Average is %f\n", rez);
    close(p_to_c[1]);
    close(c_to_p[0]);
  }
  return 0;
}
