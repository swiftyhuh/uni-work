#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  // Give any number of wornds as cmd args
  // One child procces per arg -> count vowels
  // Parent reports total number of vowels
  // Pass tje cd args through pipe to the child
  int p2c[argc - 1][2];
  int c2p[argc - 1][2];
  for (int i = 1; i < argc; i++) {
    if (pipe(p2c[i - 1]) < 0) {
      perror("oh no");
      exit(1);
    }
    if (pipe(c2p[i - 1]) < 0) {
      perror("oh no");
      exit(1);
    }
  }
  for (int i = 1; i < argc; i++) {
    int f = fork();
    if (f == -1) {
      perror("Error on creating child process");
      exit(1);
    } else if (f == 0) {
      // child process
      close(p2c[i - 1][1]);
      close(c2p[i - 1][0]);
      int len = 0;
      read(p2c[i - 1][0], &len, sizeof(int));
      char *buf = malloc(sizeof(char) * (len + 1));
      int k = read(p2c[i - 1][0], buf, len * sizeof(char));
      if (k < 0) {
        perror("Error reading string");
      } else {
        buf[k] = 0;
        printf("Child %d received %s\n", i, buf);
        int result = 0;
        for (int j = 0; j < k; j++) {
          if (strchr("aeiouAEIOU", buf[j]) != NULL)
            result++;
        }
        if (0 > write(c2p[i - 1][1], &result, sizeof(int)))
          perror("Error writing the result to parent");
      }
      free(buf);
      close(p2c[i - 1][0]);
      close(c2p[i - 1][1]);
      exit(0);
    }
  }
  // parrent process
  for (int i = 1; i < argc; i++) {
    close(p2c[i - 1][0]);
    close(c2p[i - 1][1]);
    int n = strlen(argv[i]);
    write(p2c[i - 1][1], &n, sizeof(int));
    write(p2c[i - 1][1], argv[i], n * sizeof(char));
  }
  int total = 0;
  for (int i = 1; i < argc; i++) {
    int count = 0;
    read(c2p[i - 1][0], &count, sizeof(int));
    total += count;
  }
  for (int i = 1; i < argc; i++) {
    wait(NULL);
  }
  for (int i = 1; i < argc; i++) {
    close(p2c[i - 1][1]);
    close(c2p[i - 1][0]);
  }
  printf("Total is: %d\n", total);
  return 0;
}
// unde optimizarea conteaza mai mult, facem acel int n = strlen(argv[i]);
// exectia paralele, nu in serie
