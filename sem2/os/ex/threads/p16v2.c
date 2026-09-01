#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int freq[10];
pthread_mutex_t mtx;

void *f(void *arg){
	char *s = (char *)arg;
	int len = strlen(s);
	for(int i = 0; i < len; i++){
		if(s[i] >='0' && s[i] <= '9'){
			pthread_mutex_lock(&mtx);
			freq[s[i]-'0']++;
			pthread_mutex_unlock(&mtx);
		}
	}
	return NULL;
}

int main(int argc, char *argv[]){
	int n = argc-1;
	pthread_t *th = malloc(sizeof(pthread_t)*n);
	
	for(int  i = 0 ; i < 10; i++)
		freq[i] = 0;

	pthread_mutex_init(&mtx, NULL);
	
	for(int i = 0; i < n; i++){
		pthread_create(&th[i], NULL, f, argv[i+1]);
	}
	for(int i = 0; i < n; i++){
		pthread_join(th[i], NULL);
	}
	for(int i = 0; i < 10; i++){
		printf("Freq[%d] = %d\n", i, freq[i]);
	}
	pthread_mutex_destroy(&mtx);
	free(th);

	return 0;
}
