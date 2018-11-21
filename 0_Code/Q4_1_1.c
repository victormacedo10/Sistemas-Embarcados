#include<stdio.h>
#include<stdlib.h>

int main()
{
	unsigned long long fib[100];
	FILE *fp;
	fib[0]=0;
	fp = fopen("fibonacci.bin","wb");
	fib[1]=1;
	fprintf(fp, "%lld ", fib[0]);
	fprintf(fp, "%lld ", fib[1]);
	for(int i=2;i<100;i++)
	{
		fib[i] = fib[i-1]+fib[i-2];
		fprintf(fp, "%lld ", fib[i]);
	}
	fclose(fp);
	return 0;
}