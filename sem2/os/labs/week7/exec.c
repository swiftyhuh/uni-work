#include <stdio.h>
#include <unistd.h>
int main() {

  execl("ls", "ls", "-l", NULL);
  printf("asdwabdkwbadwa\n");
  return 0;
}
