#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

int main() {
	int pid;
	int fd[2];

	int i;
	char m[100];
	char m1[]= "Pai, qual é a verdadeira essência da sabedoria?";
	char m2[]= "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.";
	char m3[]= "Mas até uma criança de três anos sabe disso!";
	char m4[]= "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...";

	pipe(fd);
	pid = fork();

	if(pid != 0)
	{
		sleep(1);
		
		// ler m1
		if(read(fd[0], m, 100) >= 0) 
			printf("\nFILHO: %s\n", m);

		// ler m2
		if (write(fd[1], m2, sizeof(m2)) < 0)
			printf("\nErro na escrita do pipe\n");

		sleep(2);

		// ler m3
		if(read(fd[0], m, 100) >= 0) 
			printf("\nFILHO: %s\n", m);

		// ler m4
		if (write(fd[1], m4, sizeof(m4)) < 0)
			printf("\nErro na escrita do pipe\n");

		sleep(3);

	}
	else
	{
		// escrever m1
		if (write(fd[1], m1, sizeof(m1)) < 0)
			printf("\nErro na escrita do pipe\n");

		sleep(2);

		// escrever m2
		if(read(fd[0], m, 100) >= 0) 
			printf("\nPAI: %s\n", m);

		// escrever m3
		if (write(fd[1], m3, sizeof(m3)) < 0)
			printf("\nErro na escrita do pipe\n");

		sleep(2);

		// escrever m4
		if(read(fd[0], m, 100) >= 0) 
			printf("\nPAI: %s\n", m);

		sleep(3);
	}
	return 0;
}