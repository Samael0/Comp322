#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

int userFile = 0;

void ParseFile(){ //Read the input 
	int rresp = 0;
	char * byte;
	byte = malloc(sizeof(char)*8); 
	char ch;
	int decimal = 0, count = 0;
	while ((rresp = read(userFile, &ch, 1))) {
		if ((ch != '0' && ch != '1') || count >= 8) {
			//decimal = decimal * pow(2, (-1*(8-count)));
			/*
			if (parityCount%2 == 0) {
				parity = "Even";
				
			} else {
				parity = " Odd";
			}
			*/
			for (int i = count; i < 8; i++) {
				byte[i] = '0';
				
			}
			printf("%8s %8c %8d ", byte, decimal, decimal);
			printf("\n");
			decimal = 0, count = 0;
			if (ch != '0' || ch != '1') {
				continue;
			}
		}
		if (ch == '1') {
			if (count != 0) {
				decimal += pow(2, (7-count));
			}
		} 
		byte[count] = ch;
		count++;
	}

}

int main(int argc, char *argv[]){

	int i=0;

	//Print the chart
	printf("Original\t ASCII\t Decimal\t  \tParity\n");
	printf("--------\t--------\t--------\t--------\n");

	//TEST

	if (argc > 1) {
		if (argv[1][0] != '-') {
			userFile = open(argv[1], O_RDONLY); 
		}
	}
	if (userFile < 0) {
		printf("File does not exist or corrupted!");
	}

	ParseFile();

	//TEST
	
	/*
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
	*/

	return 0;

}
