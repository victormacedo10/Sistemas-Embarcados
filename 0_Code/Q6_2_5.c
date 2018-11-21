#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int v_global = 0; //Variavel global
void incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", (int)id_atual);
	printf("v_global = %d\n",v_global);
}
int main(int argc, const char *argv[]){
	pid_t child_pid[3];
	int i;
	for(i=0;i<3;i++){
		child_pid[i] = fork();
		if(child_pid[i]==0){
			incrementa_Variavel_Global(getpid());
			return 0;
		}
		else{
			wait(NULL);
			incrementa_Variavel_Global(getpid());
		}
	}
	return 0;
}