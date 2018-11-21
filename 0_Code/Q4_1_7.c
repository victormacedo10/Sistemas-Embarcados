#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	fp = fopen(argv[2],"r");
	int occur=0;
	char s[20]={0};
	while((fscanf(fp,"%s",s))!= EOF)
	{
		printf("%s\n",s);
		if(strcmp(s,argv[1]) == 0)
		{
			occur++;
		}
	}
	printf("'%s' ocorre %d vezes no arquivo '%s'.\n",argv[1],occur,argv[2]);
	fclose(fp);
	return 0;
}