#include <stdio.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <unistd.h>

#include <string.h>

int main(int argc, char *argv[]) {

  int p_c1[2], c1_p[2];

  if (pipe(p_c1) < 0 || pipe(c1_p) < 0) {

    perror("Error on first set of pipes");

    exit(1);
  }

  int f1 = fork();

  if (-1 == f1) {

    perror("Error on child 1");

  } else if (0 == f1) {

    close(p_c1[1]);

    close(c1_p[0]);

    int len = 0;

    if (0 >= read(p_c1[0], &len, sizeof(int))) {

      perror("C1 - Error on read length");

      exit(1);
    }

    char *msg = malloc(sizeof(char) * len);

    if (0 >= read(p_c1[0], msg, sizeof(char) * len)) {

      perror("C1 - Error reading message");

      exit(1);
    }

    char *rez = malloc(sizeof(char) * len);

    int count = 0;

    for (int i = 0; i < len; i++) {

      if (msg[i] == 'a' || msg[i] == 'e' || msg[i] == 'i' || msg[i] == 'o' ||
          msg[i] == 'u' ||

          msg[i] == 'A' || msg[i] == 'E' || msg[i] == 'I' || msg[i] == 'O' ||
          msg[i] == 'U') {

        rez[count++] = msg[i];
      }
    }

    free(msg);

    rez[count++] = 0;

    if (0 > write(c1_p[1], &count, sizeof(int))) {

      perror("C1 - Error writing length");

      exit(1);
    }

    if (count > 0) {

      if (0 > write(c1_p[1], rez, sizeof(char) * count)) {

        perror("C1 - Error writing result");

        exit(1);
      }
    }

    free(rez);

    close(p_c1[0]);

    close(c1_p[1]);

    exit(0);
  }

  close(p_c1[0]);

  close(c1_p[1]);

  int p_c2[2], c2_p[2];

  if (pipe(p_c2) < 0 || pipe(c2_p) < 0) {

    perror("Error on second set of pipes");

    exit(1);
  }

  int f2 = fork();

  if (-1 == f2) {

    perror("Error on child 2");

  } else if (0 == f2) {

    close(p_c2[1]);

    close(c2_p[0]);

    int len = 0;

    if (0 >= read(p_c2[0], &len, sizeof(int))) {

      perror("C2 - Error on read length");

      exit(1);
    }

    char *msg = malloc(sizeof(char) * len);

    if (0 >= read(p_c2[0], msg, sizeof(char) * len)) {

      perror("C2 - Error reading message");

      exit(1);
    }

    char *rez = malloc(sizeof(char) * len);

    int count = 0;

    for (int i = 0; i < len; i++) {

      if (msg[i] >= '0' && msg[i] <= '9') {

        rez[count++] = msg[i];
      }
    }

    free(msg);

    rez[count++] = 0;

    if (0 > write(c2_p[1], &count, sizeof(int))) {

      perror("C2 - Error writing length");

      exit(1);
    }

    if (count > 0) {

      if (0 > write(c2_p[1], rez, sizeof(char) * count)) {

        perror("C1 - Error writing result");

        exit(1);
      }
    }

    free(rez);

    close(p_c2[0]);

    close(c2_p[1]);

    exit(0);
  }

  close(p_c2[0]);

  close(c2_p[1]);

  char *in = malloc(sizeof(char) * 100);

  scanf("%s", in);

  int len = strlen(in);

  if (0 > write(p_c1[1], &len, sizeof(int))) {

    perror("P - Error writing message length to C1");

  } else {

    if (0 > write(p_c1[1], in, sizeof(char) * len)) {

      perror("P - Error writing message to C1");
    }
  }

  if (0 > write(p_c2[1], &len, sizeof(int))) {

    perror("P - Error writing message length to C2");

  } else {

    if (0 > write(p_c2[1], in, sizeof(char) * len)) {

      perror("P - Error writing message to C2");
    }
  }

  free(in);

  int rez_len = 0;

  if (0 >= read(c1_p[0], &rez_len, sizeof(int))) {

    perror("P - Error reading length from C1");

    rez_len = 0;
  }

  if (rez_len > 0) {

    char *rez = malloc(sizeof(char) * rez_len);

    if (0 >= read(c1_p[0], rez, sizeof(char) * rez_len)) {

      perror("P - Error reading message from C1");

    } else {

      printf("First child: %s\n", rez);
    }

    free(rez);
  }

  rez_len = 0;

  if (0 >= read(c2_p[0], &rez_len, sizeof(int))) {

    perror("P - Error reading length from C2");

    rez_len = 0;
  }

  if (rez_len > 0) {

    char *rez = malloc(sizeof(char) * rez_len);

    if (0 >= read(c2_p[0], rez, sizeof(char) * rez_len)) {

      perror("P - Error reading message from C1");

    } else {

      printf("Second child: %s\n", rez);
    }

    free(rez);
  }

  close(p_c1[1]);

  close(c1_p[0]);

  close(p_c2[1]);

  close(c2_p[0]);

  wait(NULL);

  wait(NULL);

  return 0;
}
