#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <ctype.h>
#define bool int

int userFile = 0;
int fd;
int dec;
int count;
size_t c;
char *filename;
char *token;
char ascii[6] = "0";
char parity[5];
char asciibuffer[2] = "0";
char *extra[] = {
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
    " BS", " HT", " LF", " VT", " FF", " CR", " SO", " SI",
    "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
    "CAN", " EM", "SUB", "ESC", " FS", " GS", " RS", " US",
    "space", "DEL"};

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
	char *str;
	str = (char*)malloc(9);
	char *str1;
	str1 = (char*)malloc(1500);
	filename = argv[1];
	fd = open(filename, O_RDONLY);

	if(argc == 1){ //User did not provide anything
		printf("No elements or file given");
		return 0;
	}
	else if(argc == 2 && argv[1][0] == '-'){ //User only provided a dash
		printf("No elements or file given");
		return 0;
	}
	else if(fd == -1){ //User is using stdin
		if(strcmp(argv[1], "-") == 0){ //User is using a dash
			if (argc == 2){
				printf("No values inputted");
				return 0;
			}
			strcat(str1, argv[2]);
			for(int i = 3; i < argc; i++){
				strcat(str1, " ");
				strcat(str1, argv[i]);
			}
		}
		else{ //User is not using a dash
			strcat(str1, argv[1]);
			for(int i = 2; i < argc; i++){
				strcat(str1, " ");
				strcat(str1, argv[i]);
			}
		}
		
		printf("Original ASCII    Decimal  Parity \n");
		printf("-------- -------- -------- -------- \n"); 
		
		//Break into smaller strings
		token = strtok(str1, " ");
		
		while(token != NULL){
			while(strlen(token) > 0) {
				//More than 8
				if(strlen(token) > 8){
					strncpy(str, token, 8);
				}
				else{
					strncpy(str, token, strlen(token));
				}
				
				
				if(strlen(str) < 8){
					for(size_t i = 0; i < (8 - strlen(token)); i++){
						strcat(str, "0");
					}
				}
				
				
				*(str + 8) = 0;
				
				//Binary to decimal
				for(c = 0, dec = 0, count = 0; c < strlen(str); c++){	
					if(str[strlen(str) - (c + 1)] == 49){ //checks in reverse
						dec += 1*(pow(2,c));
						count++;
					}
				}
				
				//7 bit
				if(dec >= 128){
					dec -= 128;
				}
				//Ascii values
				if(isascii(dec)){
					if(dec == 127){
						strncpy(ascii, extra[33], 4);
					}
					else if(dec == 32){
						strncpy(ascii, extra[dec], 6);
					}
					else if(dec < 32){
						strncpy(ascii, extra[dec], 4);
					}
					else{
						asciibuffer[0] = dec;
						strncpy(ascii, &asciibuffer[0], 2);
					}
				}
				//Gets parity
				if(count % 2 == 0){
					strncpy(parity, "EVEN", 5);
				}
				else{
					strncpy(parity, "ODD", 4);
				}
				
				//Prints to table
				printf("%8s %8s %8d %8s\n", str, ascii, dec, parity);
				memset(ascii, '\0', sizeof(char)*6);

				if(strlen(token) > 8){
					token = token + 8;
				}
				else{
					token = token + strlen(token);
				}
				memset(str,0,8*sizeof(str[0]));
			}
			//Go to next token/string
			token = strtok(NULL, " ");
		}

		free(str1);
		free(str);
		return 0;
	}
	else{ //User provided a file
		//if(argv[1][0] != '-'){
			userFile = open(argv[1], O_RDONLY);
		
		//Print the chart
		printf("Original ASCII    Decimal  Parity \n");
		printf("-------- -------- -------- -------- \n"); 

		parseFile();

		return 0;
	}

	return 0;

}