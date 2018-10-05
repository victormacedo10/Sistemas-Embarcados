#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char *argv[]){
	int i;
	
	for(i=1; i<argc; i++){
		if(fork()==0){
			system(argv[i]);
			printf("%s \n", argv[i]);
			exit(0);
		}
		else
			wait(NULL);
	}
	return 0;
}

