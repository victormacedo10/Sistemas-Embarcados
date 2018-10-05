#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[]){
    for(int i=1; i<argc; i++){
    	system(argv[i]);
    }
    return 0;
}