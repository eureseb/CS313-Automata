#include <stdio.h>
#include <string.h>

#define NUMBER_OF_STRING 5
#define MAX_STRING_SIZE 256


//Main Functions
int isIdentifier(char string[]);
int isInteger(char string[]);
int isFloat(char string[]);

//test function;
void testIsIdentifer(char **arr);
void testIsInteger(char **arr);
void testIsFloat(char **arr);
void testAll(void);

int main(){
	
	testAll();
	return 0;
}
int isIdentifier(char string[]){
	int state = 0;
	char c;
	int i = 0;
	while(state!=2 && string[i] != '\0'){
		c = string[i];
		
		switch(state){
			case 0: if(isalpha(c) || c=='_') state = 1;
					else state = 2;
					break;
			case 1: if(isalpha(c) || c=='_' || isdigit(c) != 0) state = 1;
					else state = 2;
					break;
			case 2: state = 2;
					break;
		}
		i++;
	}
	return state==1;
}
int isInteger(char string[]){
	int state = 0;
	char c;
	int i = 0;
	
	while(state!=3 && string[i] != '\0'){
		c = string[i];		
		switch(state){
			case 0: if(isdigit(c) != 0)state = 1;
					else if(c=='+' || c=='-') state = 2;
					else state = 3;
					break;
			case 1:	if(isdigit(c) != 0) state = 1;
					else state = 3;
					break;
			case 2: if(isdigit(c) != 0) state = 1;
					else state = 3;
					break;
			case 3: state = 3;
					break;
		}
		i++;
	}
	return state==1;
}
int isFloat(char string[]){
	int state = 0;
	char c;
	int i = 0;
	while(state!= 5 && string[i] != '\0'){
		c = string[i];
		switch(state){
			case 0: if(isdigit(c) != 0) state = 1;
					else if(c=='+' || c=='-') state = 4;
					else if(c=='.') state = 2;
					else state = 5;
					break;
			case 1:	if(isdigit(c) != 0) state = 1;
					else if(c=='.') state = 2;
					else state = 5;
					break;
			case 2: if(isdigit(c) != 0) state = 3;
					else state = 5;
					break;
			case 3: if(isdigit(c) != 0) state = 3;
					else state = 5;
					break;
			case 4: if(isdigit(c) != 0) state = 1;
					else if(c=='.') state = 2;
					else state = 5;
					break;
			case 5: state = 5;
					break;
		}
		i++;
	}
	return state==1 || state== 3;
}

void testIsIdentifer(char **arr){
	int i;
	printf("\n[Identifiers]Testing 5 Strings:\n");
	for(i=0; i<NUMBER_OF_STRING; i++){
		printf("\n\t'%s'\t: \t", arr[i]);
		if(isIdentifier(arr[i]) == 1){
			printf("Valid Identifier\n");
		}else printf("Invalid Identifier\n");
	}
}
void testIsInteger(char **arr){
	int i;
	printf("\n\n[Integers]Testing 5 Strings:\n");
	for(i=0; i<NUMBER_OF_STRING; i++){
		printf("\t'%s'\t:\t", arr[i]);
		if(isInteger(arr[i]) == 1){
			printf("Valid Integer\n");
		}else printf("Invalid Integer\n");
	}
}
void testIsFloat(char **arr){
	int i;
	printf("\n\n[Float]Testing 5 Strings:\n");
	for(i=0; i<NUMBER_OF_STRING; i++){
		printf("\t'%s'\t:\t", arr[i]);
		if(isFloat(arr[i]) == 1){
			printf("Valid Float\n");
		}else printf("Invalid Float\n");
	}
}

void testAll(void){
	
	char *valid_identifier_strings[5] = {"_" , "_1number" , "snake_case", "camelCase", "________"};
	char *invalid_identifier_strings[5] = {"#1fanofCCS", "im_sad_:(", "3-lng-ok-na", "!BANG_BANG"," "};
	
	char *valid_integer_strings[5] = {"00100" , "+04" , "2023", "+0", "-100"};
	char *invalid_integer_strings[5] = {"0_11" , "110+" , "1+1", "1 2", "- 1"};
	
	char *valid_float_strings[5] = {"11.1" , "+.1" , "1", ".0", "-1"};
	char *invalid_float_strings[5] = {"8." , "..1" , ".", ".+0", "1.0-"};

	//Testing Identifier Strings...
	testIsIdentifer(valid_identifier_strings);
	testIsIdentifer(invalid_identifier_strings);
	
	//Testing Integer Strings...
	testIsInteger(valid_integer_strings);
	testIsInteger(invalid_integer_strings);
	
	//Testing Float Strings...
	testIsFloat(valid_float_strings);
	testIsFloat(invalid_float_strings);

}
