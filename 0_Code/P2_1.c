#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>
#include <math.h>

#define N 7

int f = 1000;
int t_2 = round((100000)/(2*f));
struct pollfd pfd;
int clk = 0;

void square_wave()
{
	t_2 = round((100000)/(2*f));
	ualarm(t_2); 
	clk = !clk;
	write(pfd->fd, &clk, 1);
}

void* sw_thread(void* dummy_ptr)
{
	system("echo 5	  > /sys/class/gpio/export");
	system("echo out   > /sys/class/gpio/gpio5/direction");
	pfd.fd = open("/sys/class/gpio/gpio4/value", O_WRONLY);
	signal(SIGALRM, square_wave);
	while(1);
	system("echo 5 > /sys/class/gpio/unexport");
	return 0;
	return NULL;
}

void poll_btn(struct pollfd *pfd)
{
	char buffer, vals[N]={0};
	int  pos=0, test=1, i, s;
	lseek(pfd->fd, 0, SEEK_SET);
	read(pfd->fd, &buffer, 1);
	poll(pfd, 1, -1);
	while(test)
	{
		lseek(pfd->fd, 0, SEEK_SET);
		read(pfd->fd, vals+pos, 1);
		vals[pos] -= '0';
		pos=(pos+1)%N;
		for(s=i=0;i<N;i++) s+=vals[i];
		if(buffer=='0')
			test = s<(N/2);
	}
}

void* poll_thread(void* dummy_ptr)
{
	struct pollfd pfd;
	int btn_press;
	int cnt = 0;
	system("echo 4	  > /sys/class/gpio/export");
	system("echo rising > /sys/class/gpio/gpio4/edge");
	system("echo in   > /sys/class/gpio/gpio4/direction");
	pfd.fd = open("/sys/class/gpio/gpio4/value", O_RDONLY);
	pfd.events = POLLPRI | POLLERR;
	while(1)
	{
		poll_btn(&pfd);
		cnt=(cnt+1)%N;
		f = pow(2, cnt)*1000;
	}
	close(pfd.fd);
	system("echo 4 > /sys/class/gpio/unexport");
	return 0;
	return NULL;
}

int main(){
	pthread_t thread1_id;
	pthread_t thread2_id;
	pthread_create (&thread1_id, NULL, &sw_thread, NULL);
	pthread_create (&thread1_id, NULL, &poll_thread, NULL);
	pthread_join (thread1_id, NULL);
	pthread_join (thread1_id, NULL);
}