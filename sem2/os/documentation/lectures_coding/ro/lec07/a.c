#include <stdio.h>
#include <pthread.h>

void* f(void* a) {
    printf("f\n");
    (void)a;
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t t;

    pthread_create(&t, NULL, f, NULL);
    printf("main\n");
    pthread_join(t, NULL);

    (void)argc;
    (void)argv;
    return 0;
}
