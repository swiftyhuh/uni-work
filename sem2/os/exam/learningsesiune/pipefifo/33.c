//33. Write a C program that creates two child process. The parent process reads one string from the keyboard (the string does not contain whitespaces) and sends it via pipe/fifo to both of its child processes. One of the child processes extracts all the vowels from the received string and the other child process extracts all the digit characters from the received string. Both child processes send what they extracted to the parent process via pipe/fifo. The parent will display the strings that are received from the child processes.

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    int p2c[2], c2p[2];
    pipe(p2c);
    pipe(c2p);
    int f = fork();
    if (f == 0){
        close(p2c[1]);
        close(c2p[0]);
        int len = 0;
        read(p2c[0], &len, sizeof(int));
        char *msg = malloc(sizeof(char)*len);
        read(p2c[0], msg, sizeof(char)*len);
        char *rez = malloc(sizeof(char)*len);
        int count = 0;
        for(int i= 0; i < len; i++){
            if (msg[i] == 'a' || msg[i] == 'e' || msg[i] == 'i' || msg[i] == 'o' || msg[i] == 'u') 
                rez[count++] = msg[i];
        }
        free(msg);
        rez[count++] = 0;


}
