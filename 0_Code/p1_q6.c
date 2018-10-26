#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
	int fp;
	char conteudo[1024];
	sprintf(conteudo, "date >> %s", argv[1]);

	system(conteudo);
	sprintf(conteudo, "- NOME: %s\n" \
		"- DATA DE NASCIMENTO: %s\n" \
		"- MATRICULA: %s\n", \
		argv[2], argv[3], argv[4]);
	fp = open(argv[1], O_WRONLY | O_APPEND, S_IRWXU);
	write(fp, conteudo, strlen(conteudo));
	close(fp);
	return 0;
}