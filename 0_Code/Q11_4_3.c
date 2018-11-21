#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <termios.h>
#include <math.h>

#define N 7

int cnt=0, f=0, T=0;

void update_freq(){
	cnt = (1+cnt)%N;
	f = pow(2, cnt);
	T = (unsigned int) (1e6)/f;
}

int main(){
	int pid;
	int pid_d = getpid();
	pid = fork();
	if(pid==0){
		struct pollfd pfd;
		int buffer;
		system("echo 4 > /sys/class/gpio/export");
        system("echo in > /sys/class/gpio/gpio4/direction");
        system("echo falling > /sys/class/gpio/gpio4/edge");
        pfd.fd = open("/sys/class/gpio/gpio4/value", O_RDONLY);
        pfd.events = POLLPRI | POLLERR;
        read(pfd.fd, &buffer, 1);
        while(1){
        	lseek(pfd.fd, 0, SEEK_SET);
        	poll(&pfd, 1, -1);
        	kill(pid_d);
        }
	}
	else{
		struct pollfd pfd_d;
		signal(SIGUSR1, update_freq);
		system("echo 5 > /sys/class/gpio/export");
        system("echo out > /sys/class/gpio/gpio5/direction");
        pfd_d.fd = open("/sys/class/gpio/gpio5/value", O_WRONLY);
        int x=0;
        while(1){
        	write(pfd_d, &x, 1);
        	usleep(T);
        	x = !x;
        	write(pfd_d, &x, 1);
        	usleep(T);
        	x = !x;
        }
	}
}