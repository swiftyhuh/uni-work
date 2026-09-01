#include <stdio.h>
#include <pthread.h>

int n = 1;

void* f(void* a) {
    for(int i=0; i<n; i++) {
        printf("%s\n", (char*)a);
    }
    (void)a;
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t ta, tb;

    if(argc > 1) {
        sscanf(argv[1], "%d", &n);
    }
    pthread_create(&ta, NULL, f, "aa");
    pthread_create(&tb, NULL, f, "b");

    for(int i=0; i<n; i++) {
        printf("main\n");
    }

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    (void)argc;
    (void)argv;
    return 0;
}
