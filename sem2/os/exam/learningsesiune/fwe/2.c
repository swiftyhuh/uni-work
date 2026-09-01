#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    
    if(argc != 2){
        perror("Please provide exactly one argument!");
        exit(0);
    }

    int n = atoi(argv[1]);
    for(int i = 0; i < n; i++){
        int f = fork();
        if(f == -1){
            perror("Error on fork");
            exit(0);
        }
        else if(f == 0)
            printf("Child procces %d - PID: %d - PPID %d\n", i, getpid(), getppid());
        else{
            wait(0);
            exit(0);
        }
    }
    return 0;
}
  
