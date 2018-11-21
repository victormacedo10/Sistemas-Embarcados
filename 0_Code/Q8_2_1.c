#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct NUM_STRUCT
{
	int num;
};
typedef NUM_STRUCT num_struct;

void *print_num(void *parameters)
{
	num_struct *p = (num_struct*)parameters;
	int i;
	for(i=0;i<10;i++)
	{
		printf("%d\n",p->num);
		sleep(1);
	}
	return NULL;
}
int main(int argc, char *argv[]){
 	pthread_t thread_id1;
 	num_struct thread_args_1;
 	int i;
 	pthread_create(&thread_id1,NULL,&print_num,&thread_args_1);
 	for(i=0;i<10;i++)
 	{
 		thread_args_1.num = i+1;
 		sleep(1);
 	}
 	pthread_join(thread_id1,NULL);
 	return 0;
 }