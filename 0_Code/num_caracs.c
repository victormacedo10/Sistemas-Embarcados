#include "num_caracs.h"
#include <stdio.h>

int Num_Caracs(char *string){
	int i=0;
	while(string[i]!='\0'){
		i++;
	}
	return i;
}
