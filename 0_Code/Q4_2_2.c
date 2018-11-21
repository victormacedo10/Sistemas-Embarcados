#include<stdio.h>
#include<stdlib.h>

int main()
{
	unsigned long long fib[100];
	FILE *fp;
	fp = fopen("fibonacci.bin","rb");
	fread(fib,sizeof(unsigned long long),100,fp);
	for(int i=2;i<100;i++)
	{
		printf("%lld ", fib[i]);
	}
	fclose(fp);
	return 0;
}