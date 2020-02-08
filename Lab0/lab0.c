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
	char * byte, * par;
	byte = malloc(sizeof(char)*8), par = malloc(sizeof(char)*8); 
	par = "________";
	char ch;
	int dec = 0, count = 0, pcount = 1;
	while (rresp = read(userFile, &ch, 1)) {
		if ((ch != '0' && ch != '1') || count >= 8) {
			//dec = dec * pow(2, (-1*(8-count)));
			if (fmod(pcount, 2) == 0) {
				par = "Even";
	
			} else {
				par = " Odd";
			}
			for (int i = count; i < 8; i++) {
				byte[i] = '0';
			}
			printf("%8s %8c %8d %8s \n", byte, dec, dec, par);
			dec = 0, count = 0; pcount = 0;
			if (ch != '0' || ch != '1') {
				continue;
			}
		}
		if (ch == '1') {
			if (count != 0) {
				dec += pow(2, (7-count));
			}
			pcount++;
		} 
		byte[count] = ch;
		count++;
	}
}

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
