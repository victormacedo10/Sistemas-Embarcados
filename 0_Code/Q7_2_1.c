 #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <signal.h>
    #include <sys/signal.h>

    int main(int argc, char **argv) {
        int pid;
        int fd[2];
        int i;

        pipe(fd);
        pid = fork();

        if(pid == 0){   
            sleep(11);      
            for(int n=1; n<=10; n++){       
   				read(fd[0], &i,  sizeof(int));
   				printf("Valor lido: %d\n", i);
            }   
		}
        else{
            for(int n=1; n<=10; n++){       
	            write(fd[1], &n, sizeof(n));
	            sleep(1);
            }    
        }
        return 0;
    }