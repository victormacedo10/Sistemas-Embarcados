#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#define N 100

int sample = 0, d[N], ms = 0;
int fd;
double m=0.0;
int i2c_fd;

void loop(int sig)
{
	unsigned int msp430_ret, pi_out;

	ualarm(10000);
	pi_out = 0x55;
	write(i2c_fd, &pi_out, 1);
	read(i2c_fd, &msp430_ret, 1);
	d[sample] = (unsigned int)msp430_ret;
	read(i2c_fd, &msp430_ret, 1);
	d[sample] += ((unsigned int)msp430_ret)<<8;
	m += (double) d[sample];
	sample = (sample+1)%N;
	if(sample==0)
	{
		m = 0.0;
		ms++;
	}
	if(ms==N)
	{
		printf("Valor medio = %f V\n",m*3.0/1023.0/N);
	}
}

int main(void)
{
	unsigned char msp430_ret, slave_addr=0x0F;
	signal(SIGALRM, loop);
	ioctl(i2c_fd, I2C_SLAVE, slave_addr);
	i2c_fd; = open("/dev/i2c-1", O_RDWR);
	ualarm(10000);
	while(1);
}