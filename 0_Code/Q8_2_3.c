#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define TAM 50000

struct VECTOR
{
	long int *vec;
	double m;
};
typedef VECTOR vector;

void *find_mean(void *mean)
{
	vector *p = (vector *) mean;
	p->m = 0;
	int i;
	for(i=0;i < (TAM)/4;i++)
	{
		p->m += p->vec[i];
	}
	p->m = (p->m)/(TAM/4);
	return NULL;
}

int main()
{
	long int vec[TAM];
	srand(time(NULL));
	int i;
	
	for(i=0;i<TAM;i++)
	{
		vec[i] = rand() % 1000;
	}
	
	double mean;
	mean = 0;

	for(i=0;i<TAM;i++)
	{
		mean += vec[i];
	}
	mean = mean/TAM;

	printf("Busca completa no vetor: %.2lf.\n",mean);
	vector thread_vector[4];
	pthread_t thread_id[4];
	
	for(i=0;i<4;i++)
	{
		thread_vector[i].vec = &vec[(TAM/4)*i];
		pthread_create(&thread_id[i],NULL,&find_mean,&thread_vector[i]);
	}

	for(i=0;i<4;i++)
		pthread_join(thread_id[i],NULL);

	mean = 0;
	
	for(i=0;i<4;i++)
	{
		mean += thread_vector[i].m;
	}
	
	mean = mean/4;
	printf("Busca paralela em threads: %.2lf.\n",mean);

	return 0;
}