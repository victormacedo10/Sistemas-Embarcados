#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	char * l_a[2];
	l_a[0] = "ls";
	l_a[1] = NULL;
    for(int i=1; i<argc; i++){
    	pid_t pid_filho = fork();
    	if (pid_filho == 0){
    		l_a[0] = argv[i];
    		execvp(l_a[0], l_a);
    	}
    }
    return 0;
}