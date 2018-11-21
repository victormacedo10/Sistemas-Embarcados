#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>


int main() {
	int pid;
	int fd[2];
	char mensagem[100];
	char m1[]= "FILHO1: Quando o vento passa, é a bandeira que se move.";
	char m2[]= "FILHO2: Não, é o vento que se move.";
	char m3[]= "PAI: Os dois se enganam. É a mente dos senhores que se move.";
	pipe(fd);

	pid = fork();

	if(pid == 0)
	{
		// escrita filho 1 para filho 2
		if (write(fd[1], m1, sizeof(m1)) < 0)
			printf("Erro na escrita do pipe\n");
		
		sleep(2);

		// escrita filho 1 para pai
		if (write(fd[1], m1, sizeof(m1)) < 0)
			printf("Erro na escrita do pipe\n");

		sleep(3);

		// ler filho 2
		if(read(fd[0], mensagem, 100) < 0) 
			printf("Erro na leitura do pipe\n");

		sleep(2);

		// ler pai
		if(read(fd[0], mensagem, 100) < 0) 
			printf("Erro na leitura do pipe\n");

		sleep(2);
	}
	else
	{
		pid = fork();

		if(pid == 0)
		{	
			sleep(1);

			// ler filho 1
			if(read(fd[0], mensagem, 100) < 0) 
				printf("Erro na leitura do pipe\n");

			sleep(2);

			// escrita filho 2 para filho 1
			if (write(fd[1], m2, sizeof(m2)) < 0)
				printf("Erro na escrita do pipe\n");

			sleep(2);

			// escrita filho 2 para pai
			if (write(fd[1], m2, sizeof(m2)) < 0)
				printf("Erro na escrita do pipe\n");

			sleep(4);

			// ler pai
			if(read(fd[0], mensagem, 100) < 0) 
				printf("Erro na leitura do pipe\n");

			sleep(2);
		}
		else
		{
		sleep(3);

		// ler filho 1;
		if(read(fd[0], mensagem, 100) < 0) 
			printf("Erro na leitura do pipe\n");

		sleep(3);

		// ler filho 2
		if(read(fd[0], mensagem, 100) < 0) 
			printf("Erro na leitura do pipe\n");
		}
///////////////////////////////////////////////////////////////////////////////
//////////			PAI ESCREVE para FILHO 1
///////////////////////////////////////////////////////////////////////////////

		printf("PAI vai escrever no pipe\n");
		if (write(fd[1], m3, sizeof(m3)) < 0)
			printf("Erro na escrita do pipe\n");
		printf("PAI terminou de escrever no pipe\n");
	sleep(2);
///////////////////////////////////////////////////////////////////////////////
//////////			PAI ESCREVE para FILHO 2
//////////////////////////////////////////////////////////////////////////////
		printf("PAI vai escrever no pipe\n");
		if (write(fd[1], m3, sizeof(m3)) < 0)
			printf("Erro na escrita do pipe\n");
		printf("PAI terminou de escrever no pipe\n");
	sleep(2);
	}
	return 0;
}