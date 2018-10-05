#include <stdio.h>
#include <stdlib.h>
#include "num_caracs.h"

int main(int argc, char **argv){
	int j;
	for(int i=0;i<argc;i++){
        printf("Argumento: %s / Numero de caracteres: %d \n", \
        	argv[i], Num_Caracs(argv[i]));
    }
    return 0;
}