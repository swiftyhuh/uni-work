#include <stdio.h>
#include <pthread.h>

int m[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
pthread_mutex_t mx, m0;

void* fx(void* a) {
    while(1) { int played = 0;
        pthread_mutex_lock(&mx);
        for(int i=0; i<3; i++) { for(int j=0; j<3; j++) {
            if(!played && m[i][j] == -1) { m[i][j] = 1; played = 1; } } }
        pthread_mutex_unlock(&m0);
        if(!played) break;
    } (void)a; return NULL;
}

void* f0(void* a) {
    while(1) { int played = 0;
        pthread_mutex_lock(&m0);
        for(int i=0; i<3; i++) { for(int j=0; j<3; j++) {
            if(!played && m[i][j] == -1) { m[i][j] = 0; played = 1; } } }
        pthread_mutex_unlock(&mx);
        if(!played) break;
    } (void)a; return NULL;
}

int main(int argc, char** argv) {
    pthread_t tx, t0;
    pthread_mutex_init(&mx, NULL);
    pthread_mutex_init(&m0, NULL);
    pthread_mutex_lock(&m0);
    pthread_create(&tx, NULL, fx, NULL);
    pthread_create(&t0, NULL, f0, NULL);
    pthread_join(tx, NULL);
    pthread_join(t0, NULL);
    pthread_mutex_destroy(&mx);
    pthread_mutex_destroy(&m0);

    (void)argc;
    (void)argv;
    return 0;
}


