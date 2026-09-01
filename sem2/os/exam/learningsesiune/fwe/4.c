// 4. Write a C program that runs a bash command (potentially with arguments)
// received as a command line argument and times its execution.
// ex: ./exe grep -E -c "^[a-z]{4}[0-9]{4}" /etc/passwd"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>

int main(int argc, char* argv[]){
   struct timeval tv1, tv2;
   if(argc < 2){
       perror("Please provide at least one argument!");
       exit(0);
   }
   gettimeofday(&tv1, NULL);
   int f = fork();
   if(f == -1){
       perror("Error on fork");
       exit(0);
   } else if(f == 0){
       if(execvp(argv[1], argv+1) == -1){
           perror("error running the given command");
           exit(0);
       }
   } else{
       wait(0);
       gettimeofday(&tv2, NULL);
       printf("Totla time = %f seconds\n", (double)(tv2.tv_usec - tv1.tv_usec)/1000000 + (double)(tv2.tv_sec - tv1.tv_sec));
   }
   return 0;

}
