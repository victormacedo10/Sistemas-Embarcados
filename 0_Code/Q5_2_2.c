#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, const char * argv[])
{
	int fp;
	fp = open("ola_usuario_1.txt", O_RDWR | O_CREAT, S_IRWXU);
	char name[30],age[20],str[50];
	printf("Digite o seu nome: ");
	gets(name);
	printf("\nDigite a sua idade: ");
	gets(age);
	strcpy(str,"nome: ");
	strcat(str,name);
	strcat(str,"\n");
	strcat(str,"idade: ");
	strcat(str,age);
	strcat(str,"\n");
	printf("%s\n",str);
	write(fp,str,strlen(str)*sizeof(char));
	close(fp);
	return 0;
}