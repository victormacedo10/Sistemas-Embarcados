#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

struct VECTOR{
	long long int *vec;
	long long int max;
};
typedef VECTOR vector;

void *find_max(void *max){
	vector *p = (vector *) max;
	p->max = 0;
	int i;
	for(i=0;i < 12500;i++){
		if(p->max < p->vec[i]){
			p->max = p->vec[i];
		}
	}

	return NULL;
}

int main(int argc, char *argv[]){
	long long int vec[50000];
	srand(time(NULL));
	int i;
	
	for(i=0;i<50000;i++){
		vec[i] = rand() % 100001;
	}
	
	long long int max;
	max = 0;

	for(i=0;i<50000;i++){
		if(vec[i]>max){
			max = vec[i];
		}
	}
	
	printf("Busca completa no vetor: %lld \n",max);
	vector thread_vector[4];
	pthread_t thread_id[4];
	
	for(i=0;i<4;i++){
		thread_vector[i].vec = &vec[12500*i];
		pthread_create(&thread_id[i],NULL,&find_max,&thread_vector[i]);
	}
	for(i=0;i<4;i++)
		pthread_join(thread_id[i],NULL);
	max = 0;
	for(i=0;i<4;i++){
		if(max < thread_vector[i].max){
			max = thread_vector[i].max;
		}
	}
	printf("Busca paralela em threads: %lld \n",max);

	return 0;
}