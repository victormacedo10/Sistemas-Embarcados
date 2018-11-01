#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[]){
	system("hcitool scan | grep -c '98:D3:31:60:3F:4E' >> status.txt");
	return 0;
}