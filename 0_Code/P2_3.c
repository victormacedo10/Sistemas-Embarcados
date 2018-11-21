#include <stdio.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <unistd.h>

#define N 100

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
		else
			test = s>(N/2);
	}
}

int main(void)
{

	struct pollfd pfd;
	int btn_press;
	system("echo 4	  > /sys/class/gpio/export");
	system("echo both > /sys/class/gpio/gpio4/edge");
	system("echo in   > /sys/class/gpio/gpio4/direction");
	pfd.fd = open("/sys/class/gpio/gpio4/value", O_RDONLY);
	pfd.events = POLLPRI | POLLERR;
	for(btn_press=0; btn_press<5; btn_press++)
	{
		puts("Pressione o botao...");
		poll_btn(&pfd);
		puts("Borda de descida!");
		poll_btn(&pfd);
		puts("Borda de subida!");
	}
	close(pfd.fd);
	system("echo 4 > /sys/class/gpio/unexport");
	return 0;
}