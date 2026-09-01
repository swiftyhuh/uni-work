#include <stdio.h>
#include <pthread.h>

int n = 0;
pthread_mutex_t m;

void* f(void* a) {
    for(int i=0; i<(int)(long)a; i++) {
        pthread_mutex_lock(&m);
        n++;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t t[10];
    int k = 1;

    if(argc > 1) {
        sscanf(argv[1], "%d", &k);
    }

    pthread_mutex_init(&m, NULL);
    for(int i=0; i<10; i++) {
        pthread_create(&t[i], NULL, f, (void*)(long)k);
    }
    for(int i=0; i<10; i++) {
        pthread_join(t[i], NULL);
    }
    pthread_mutex_destroy(&m);
    printf("%d\n", n);

    (void)argc;
    (void)argv;
    return 0;
}
