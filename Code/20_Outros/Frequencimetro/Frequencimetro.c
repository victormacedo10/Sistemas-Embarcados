#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>

// Usar GPIO Pino 4, que é Pino 0 na wiringPi
#define PINO_ENT 7

#define T_AMOSTRAGEM 2000000000ul

unsigned long contagem_eventos;
struct timespec t[2];

void conta_eventos(void)
{
	if(contagem_eventos==0)
		clock_gettime(CLOCK_MONOTONIC, &t[0]);
	else
		clock_gettime(CLOCK_MONOTONIC, &t[1]);
	contagem_eventos++;
}

void sleep_until(struct timespec *ts, unsigned long delay)
{
	while(delay >= 1000000000ul)
	{
		ts->tv_sec++;
		delay -= 1000000000ul;
	}
	ts->tv_nsec += delay;
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, ts,  NULL);
}

int main(void)
{
	struct timespec ts;
	double freq;
	wiringPiSetup();
	wiringPiISR(PINO_ENT, INT_EDGE_FALLING, &conta_eventos);
	while(1)
	{
		printf("Medir freq: ENTER / Sair: CTRL-C ");
		getchar();
		contagem_eventos = 0;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		sleep_until(&ts, T_AMOSTRAGEM);
		freq  = (double)t[1].tv_sec;
		freq -= (double)t[0].tv_sec;
		freq += ((double)t[1].tv_nsec)*1.0e-9;
		freq -= ((double)t[0].tv_nsec)*1.0e-9;
		freq /= (double)(contagem_eventos-1);
		freq = 1.0/freq;
		if(freq>=1.0e6)
			printf("Frequencia = %f MHz\n", freq*1.0e-6);
		else if(freq>=1.0e3)
			printf("Frequencia = %f kHz\n", freq*1.0e-3);
		else
			printf("Frequencia = %f Hz\n", freq);
	}
	return 0;
}
