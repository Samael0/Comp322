#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#define bool int

int userFile = 0;

int decimalConversion(char *n){ //Convert from binary to decimal
    int decimalConversion = 0, i = 0, remainder;
    int numConversion = atoi(n);
    while(numConversion != 0){
        remainder = numConversion % 10;
        numConversion /= 10;
        decimalConversion += remainder * pow(2, i);
        ++i;
    }

    return decimalConversion;

}

bool getParity(int n){ //Calculate the parity
    bool parity = 0;
    while (n){
        parity = !parity;
        n = n & (n - 1);
    }

    return parity;
}

void parseFile(){ //Read the input and convert to ASCII and Decimal 
	int x = 0;
	int decimal = 0;
	int count = 0;
	char * byte;
	char ch;
	byte = malloc(sizeof(char)*8); 
	while((x = read(userFile, &ch, 1))){
		if((ch != '0' && ch != '1') || count >= 8){
			for(int i = count; i < 8; i++){
				byte[i] = '0';
				
			}
			printf("%8s %8c %8d %8s", byte, decimal, decimal, getParity(decimalConversion(byte)) ? "ODD" : "EVEN");
			printf("\n");
			decimal = 0, count = 0;
			if(ch != '0' || ch != '1'){
				continue;
			}
		}
		if(ch == '1'){
			if(count != 0){
				decimal += pow(2, (7-count));
			}
		} 
		byte[count] = ch;
		count++;
	}

}

int main(int argc, char *argv[]){

	if(argc == 1){
		printf("No elements or file given");
		return 0;
	}
	else if(argc == 2 && argv[1][0] == '-'){
		printf("No elements or file given");
		return 0;
	}
	else if(argc > 1){
		if(argv[1][0] != '-'){
			userFile = open(argv[1], O_RDONLY);
		}
	}
	else if(argc >= 2){
		if(argv[1][0] == '-'){
			
		}
		else{

		}
	}	
	
	//Print the chart
	printf("Original ASCII    Decimal  Parity \n");
	printf("-------- -------- -------- -------- \n"); 

	parseFile();

	return 0;

}
