#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
  // int pid = fork();
  // if (pid == 0)
  //   printf("pula\n");
  // else {
  //   wait(0);
  //   printf("Hello world\n");
  // }
  //   int pid = fork();
  //
  //   if (pid == 0) {
  //     printf("child working\n");
  //     exit(0);
  //   }
  //
  //   wait(0);
  //   printf("parent after child finished\n");
  //
  // int n = 5;
  // for (int i = 0; i < n; i++) {
  //   int pid = fork();
  //
  //   if (pid == 0) {
  //     printf("Child %d PID=%d, ParentPID=%d\n", i, getpid(), getppid());
  //     exit(0);
  //   }
  // }
  //
  // for (int i = 0; i < n; i++) {
  //   wait(0);
  // }
  // printf("before\n");
  // execlp("ls", "ls", "-l", NULL);
  // printf("after\n");
}
