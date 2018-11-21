#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>

int main(void) {
	int pid_filho_1, pid_filho_2, pid_filho_3,  pid;	// PIDs dos processos
	int fd[2];	// Descritores do pipe
	int i;
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();
	// Codigo do filho
	if(pid == 0)
	{	
		printf("Filho espera o Pai.\n");
		sleep(11);		
		for(int n=1; n<=10; n++)
		{		
			if (read(fd[0], &i,  sizeof(int)) < 0)
				printf("Erro na escrita do pipe\n");
			else
				printf("Filho leu: %d\n", i);
		}
		printf("Filho se encerra.\n");		

	}
	// Codigo do pai
	else
	{
		printf("Pai vai escrever no pipe\n");
		for(int n=1; n<=10; n++)
		{		
		if (write(fd[1], &n, sizeof(n)) < 0)
			printf("Erro na escrita do pipe\n");
		printf("Pai espera 1 seg\n");
		sleep(1);
		}
		printf("Pai se encerra.\n");		
	}
	return 0;
}