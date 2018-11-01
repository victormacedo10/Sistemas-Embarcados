#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <string.h>

int main(int argc, const char * argv[]) {

	char nome_arquivo[] = "Ola_mundo.txt";
	char string[] = "Ola mundo!";
	int fp;
    
	fp = open(nome_arquivo, O_WRONLY | O_CREAT);
	write(fp, string, strlen(string)*sizeof(char));		
	close(fp);
	return 0;
}