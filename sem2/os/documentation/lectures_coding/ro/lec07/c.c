#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* f(void* a) {
    printf("%d\n", (int)(long)a);
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t t[10];

    for(int i=0; i<10; i++) {
        pthread_create(&t[i], NULL, f,
                       (void*)(long)i);
    }
    for(int i=0; i<10; i++) {
        pthread_join(t[i], NULL);
    }

    (void)argc;
    (void)argv;
    return 0;
}
