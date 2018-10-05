#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAM 16

struct vectors{
	int *v1, *v2;
	int N;
	long int sp;
};

int i;

void* thread_function(void* params){
	struct vectors* p = (struct vector*) params;
	int i;
	p->sp = 0;
	for(i = 0; i < p->N; i++)
		p->sp += ((long int)(p->v1[i]))*((long int)(p->v2[i]));
	return NULL;
}

int main(){
	pthread_t threads[4];
	struct vectors vecs[4];
	int v1[TAM], v2[TAM];
	long int valor_final = 0;
	int i;

	srand(time(NULL));
	for(i = 0; i<TAM; i++){
		v1[i] = rand()&0xFF;
		v2[i] = rand()&0xFF;
	}
	for(i=0; i<4; i++){
		vecs[i].v1 = &(v1[i*(TAM/4)]);
		vecs[i].v2 = &(v2[i*(TAM/4)]);
		vecs[i].N = (TAM/4);
		pthread_create(&(threads[i]), NULL, \
			&thread_function, &(vecs[i]));
	}
	valor_final = 0;
	for(i=0; i<4; i++){
		pthread_join(threads[i], NULL);
		valor_final += vecs[i].sp;
	}
	printf("Result = %ld\n", valor_final);
	return 0;
}