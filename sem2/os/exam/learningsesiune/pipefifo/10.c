// 10. Create two processes A and B. A generates a random number n between 50 and 200. If it is even, it sends it to B, if it is odd it sends n+1 to B. B receives the number and divides it by 2 and sends it back to A. The process repeats until n is smaller than 5. The processes will print the value of n at each step

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int p2c[2], c2p[2];
    pipe(p2c);
    pipe(c2p);
    int f = fork();
    if ( f == 0){
        close(p2c[1]);
        close(c2p[0]);
        int n;
        while(1){
            read(p2c[0], &n, sizeof(int));
            printf("Child received %d\n",n);
            n /= 2;
            printf("Child sendig %d\n", n);
            write(c2p[1], &n, sizeof(int));
            if(n < 5)
                break;
        }
        close(p2c[0]);
        close(c2p[1]);
        exit(0);
    } else{
        close(p2c[0]);
        close(c2p[1]);
        srandom(time(0));
        int n = random()%151+50;
        printf("Parent generated %d\n", n);
        while(n >= 5){
            if(n % 2 == 1)
                n++;
            printf("Parent sending %d\n", n);
            write(p2c[1], &n, sizeof(int));
            read(c2p[0], &n, sizeof(int));
            printf("Parent received %d\n", n);
        }
        wait(0);
        close(p2c[1]);
        close(c2p[0]);
    }
    return 0;
}
