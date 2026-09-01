#include <stdlib.h>
#include "a.h"

int main(int argc, char** argv) {
    int shm = shmget(1234, sizeof(struct absp), IPC_CREAT | 0600);
    struct absp* x = shmat(shm, 0, 0);

    x->s = 1;
    x->p = 2;
    while(1) {
        x->a = rand() % 1000;
        x->b = rand() % 1000;
        if(x->s == x->p) break;
    }

    shmdt(x);
    shmctl(shm, IPC_RMID, NULL);
    (void)argc;
    (void)argv;
    return 0;
}
