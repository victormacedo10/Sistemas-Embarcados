#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[]){

	int fp;
	char c = ' ';
	int i;
	fp = open(argv[1], O_WRONLY | O_CREAT, S_IRWXU);
	for(i=2; i<argc; i++){
		write(fp, argv[i], strlen(argv[i])*sizeof(char));
		write(fp, &c, sizeof(char));
	}
	close(fp);
	return 0;

}