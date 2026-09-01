#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define H 10
#define B 5

int honey = 0;
pthread_mutex_t m;
pthread_cond_t c;
pthread_barrier_t b;
sem_t s;

void* hive(void*) {
    while(1) {
        pthread_mutex_lock(&m);
        honey++;
        printf("+");
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void* bear(void* a) {
    // hand washing
    pthread_barrier_wait(&b);
    while(1) {
        sem_wait(&s);
        pthread_mutex_lock(&m);
        if(honey < 5) {
            printf("!");
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
            continue;
        }
        honey -= 5;
        printf("-");
        pthread_mutex_unlock(&m);
        sem_post(&s);
    }
    (void)a;
    return NULL;
}

void* ranger(void* a) {
    while(1) {
        pthread_mutex_lock(&m);
        while(honey >= 5) {
            printf("v");
            pthread_cond_wait(&c, &m);
            printf("^");
        }
        honey += 20;
        printf("@");
        pthread_mutex_unlock(&m);
    }
    (void)a;
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t hives[H], bears[B], guy;

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);
    pthread_barrier_init(&b, NULL, B);
    sem_init(&s, 0, 3);

    for(int i=0; i<H; i++)
        pthread_create(&hives[i], NULL, hive, NULL);
    for(int i=0; i<B; i++)
        pthread_create(&bears[i], NULL, bear, NULL);
    pthread_create(&guy, NULL, ranger, NULL);

    for(int i=0; i<H; i++)
        pthread_join(hives[i], NULL);
    for(int i=0; i<B; i++)
        pthread_join(bears[i], NULL);
    pthread_join(guy, NULL);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);
    pthread_barrier_destroy(&b);
    sem_destroy(&s);

    (void)argc;
    (void)argv;
    return 0;
}
