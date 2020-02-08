#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int userFile;

int main(int argc, char** argv){

	int i=0;

	//Print the chart
	printf("Original\t ASCII\t Decimal\t  \tParity\n");
	printf("--------\t--------\t--------\t--------\n");

	//Try to open a file
	//Using stdin because of no arguments
	if(argc == 1){
		userFile = stdin;
		ParseFile(); //to be implemented
	}
	else{
		for(i=1;i<argc;i++){
			if(strcmp(argv[i], "-") == 0){ //Using input from stdin
				userFile = stdin;
				ParseFile(); //to be implemented
			}

			else{
				if(access(argv[i], 0) != -1){ //The file exists to open
					userFile = open(argv[i], 0);
					ParseFile(); //to be implemented
				}	
			}
		}
	}

	return 0;

}
