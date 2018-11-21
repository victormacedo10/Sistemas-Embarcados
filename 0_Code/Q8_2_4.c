#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define TAM 50000

struct VECTOR{
	long int *vec;
	double m;
	long double v;
};
typedef VECTOR vector;

void *find_mean(void *mean){
	vector *p = (vector *) mean;
	int i;
	p->m = 0;

	for(i=0;i < (TAM)/4;i++){
		p->m += p->vec[i];
	}
	p->m = (p->m)/(TAM/4);
	return NULL;
}

void *find_var(void *var){
	vector *p = (vector *) var;
	int i;
	p->v = 0;
	for(i=0;i < (TAM)/4; i++){
		p->v += pow(p->vec[i] - p->m,2);
	}
}

int main(){
	long int vec[TAM];
	srand(time(NULL));
	int i;

	for(i=0;i<TAM;i++){
		vec[i] = rand() % 1000;
	}
	
	double mean;
	long double var;
	mean = 0;
	
	for(i=0;i<TAM;i++){
		mean += vec[i];
	}

	mean = mean/TAM;
	
	var = 0;

	for(i=0;i<TAM;i++){
		var += pow(vec[i]-mean,2);
	}
	var = var/TAM;
	
	printf("Busca completa no vetor: %.2Lf.\n",var);

	vector thread_vector[4];
	pthread_t thread_id[4];
	
	for(i=0;i<4;i++){
		thread_vector[i].vec = &vec[(TAM/4)*i];
		pthread_create(&thread_id[i],NULL,&find_mean,&thread_vector[i]);
	}

	for(i=0;i<4;i++)
		pthread_join(thread_id[i],NULL);

	mean = 0;

	for(i=0;i<4;i++){
		mean += thread_vector[i].m;
	}
	
	mean = mean/4;
	
	for(i=0;i<4;i++){
		thread_vector[i].vec = &vec[(TAM/4)*i];
		thread_vector[i].m = mean;
		pthread_create(&thread_id[i],NULL,&find_var,&thread_vector[i]);
	}

	for(i=0;i<4;i++)
		pthread_join(thread_id[i],NULL);

	var = 0;

	for(i=0;i<4;i++){
		var += thread_vector[i].v;
	}
	var = var/TAM;

	printf("Busca paralela em threads: %.2Lf.\n",var);

	return 0;
}