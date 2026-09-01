#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define S 10
#define U 7

int miere = 0;
pthread_mutex_t m;
pthread_cond_t c;
sem_t s;
pthread_barrier_t b;

void* stup(void* a) {
    while(1) {
        pthread_mutex_lock(&m);
        miere++;
        printf("+");
        pthread_mutex_unlock(&m);
    }
    (void)a;
    return NULL;
}

void* urs(void* a) {
    // spalare pe maini
    pthread_barrier_wait(&b);
    while(1) {
        sem_wait(&s);
        pthread_mutex_lock(&m);
        if(miere < 5) {
            pthread_cond_signal(&c);
            printf("!");
            pthread_mutex_unlock(&m);
            sem_post(&s);
            continue;
        }
        miere -= 5;
        printf("-");
        pthread_mutex_unlock(&m);
        sem_post(&s);
    }
    (void)a;
    return NULL;
}

void* padurar(void* a) {
    while(1) {
        pthread_mutex_lock(&m);
        while(miere >= 5) {
            printf("v");
            pthread_cond_wait(&c, &m);
            printf("^");
        }
        printf("@");
        miere += 20;
        pthread_mutex_unlock(&m);
    }
    (void)a;
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t stupi[S], ursi[U], padu;

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);
    sem_init(&s, 0, 3);
    pthread_barrier_init(&b, NULL, U);

    for(int i=0; i<S; i++) {
        pthread_create(&stupi[i], NULL, stup, NULL);
    }
    for(int i=0; i<U; i++) {
        pthread_create(&ursi[i], NULL, urs, NULL);
    }
    pthread_create(&padu, NULL, padurar, NULL);

    for(int i=0; i<S; i++) {
        pthread_join(stupi[i], NULL);
    }
    for(int i=0; i<U; i++) {
        pthread_join(ursi[i], NULL);
    }
    pthread_join(padu, NULL);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);
    sem_destroy(&s);
    pthread_barrier_destroy(&b);
    (void)argc;
    (void)argv;
    return 0;
}
