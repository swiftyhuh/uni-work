#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/shm.h>
#include "e.h"

int main(int argc, char** argv) {
    int shmid;
    struct absp* x;

    shmid = shmget(1234, 0, 0);
    x = shmat(shmid, 0, 0);

    srand(time(NULL));
    while(1) {
        x->s = x->a + x->b;
        x->p = x->a * x->b;
        if(x->s == x->p) break;
    }
    shmdt(x);


    (void)argc;
    (void)argv;
    return 0;
}
