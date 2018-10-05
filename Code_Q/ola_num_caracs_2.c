#include <stdio.h>
#include <stdlib.h>
#include "num_caracs.h"

int main(int argc, char **argv){
	int j=0;
	for(int i=0;i<argc;i++){
        j += Num_Caracs(argv[i]);
    }
    printf("Total de caracteres de entrada: %d \n", j);
    return 0;
}