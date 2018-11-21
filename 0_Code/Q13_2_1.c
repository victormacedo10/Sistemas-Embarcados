#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>
#include <string.h>

# define TTY "/DEV/ttyS0"

int uart0_fd;
void ctrl_c(int sig)
{
	puts("Fechando " TTY "...");
	serialClose(uart0_fd);
	exit(-1);
}
int main(void)
{
	unsigned char msp430_input=1;
	int amostras[10],i;
	double media=0;
	signal(SIGINT,ctrl_c);
	uart0_fd = serialOpen(TTY,9600);
	if(uart0_fd == -1)
	{
		puts("Erro em wiringPi().");
		return -1;
	}
	puts(TTY "aberto.");
	puts("UART configurada: ");
	system("stty -F" TTY);
	puts("");
	serialFlush(uart0_fd);
	puts("Pressione CTRL+C para encerrar o programa.\n");
	while(1)
	{
		for(i=0;i<100;i++)
		{
			amostras[i] = FF & ((unsigned char)serialGetchar(uart0_fd));
			amostras[i] |=  ((unsigned char)serialGetchar(uart0_fd) << 8);
			media += amostras[i];
			usleep(10000);
		}
		media = media/100;
		media = (media*3)/1024;
		printf("Valor medio de tensao: %.3lf V\n",media);
	}
}