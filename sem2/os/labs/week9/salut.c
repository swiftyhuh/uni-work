#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("please provide two arguments\n");
        exit(0);
    }

    if(mkfifo(argv[1], 0600)<0){
        perror("Error creating fifo\n");
        exit(1);
    }

    if(mkfifo(argv[2], 0600)<0){
        perror("Error creating fifo2\n");
        exit(1);
    }

    int fd = open(argv[1], O_WRONLY);
    if(-1 == fd){
        perror("Error on open fifo\n");
        exit(1);
    }

    int fd2 = open(argv[2], O_RDONLY);
    if(-1 == fd2){
        perror("Error on open fifo\n");
        exit(1);
    }

    int left=0;
    int right=1000;
    int guess;
    int response;

    while(left<=right){
        guess=(left+right)/2;
        printf("my guess is %d\n", guess);
        write(fd, &guess, sizeof(int));
        read(fd2, &response, sizeof(int));
        printf("Response: %d\n", response);
        if (response == 0){
            printf("Found the number %d\n", guess);
            break;
        }else if(response == -1)left = guess+1;
         else if(response == 1)right = guess-1;
    }

    close(fd);
    close(fd2);
    unlink(argv[1]);
    unlink(argv[2]);
}





    
