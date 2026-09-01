
#include "a.h"

int main(int argc, char** argv) {
    int shm = shmget(1234, 0, 0);
    struct absp* x = shmat(shm, 0, 0);

    while(1) {
        x->s = x->a + x->b;
        x->p = x->a * x->b;
        printf("% 4d + % 4d = % 5d    % 4d * % 4d = % 8d\n",
               x->a, x->b, x->s, x->a, x->b, x->p);
        if(x->s == x->p) break;
    }

    shmdt(x);

    (void)argc;
    (void)argv;
    return 0;
}
