#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBER_OF_STRING 5
#define MAX_STRING_SIZE 256

int isIdentifier(char string[]);
int isInteger(char string[]);
int isFloat(char string[]);
int isStatement(char string[]);
/*
		Statement condition:
			Identifier =(e + (+) + (-)) (Identifier + Float/Integer)(;)
			Statements accepted must be in this format: "(identifier)(space)(space)*('=')(space)(space)*(sign + e)(Identifier + Number)(;)"
			"num = +num1;" and " num   = +num1 ;" is accepted.
			"num=num1;" is not accepted.
*/

//helper functions
int endsWithSemiColon(char string[]){
	int state = 0;
	int i=0;
	while(string[i] != '\0'){
		if(string[++i] == ';' && string[i+1]=='\0'){
			state = 1;
			break;	
		}
	}
	return state;
} 
int isOper(char c){
	if(c=='+' || c=='-' || c=='/' || c=='*' || c=='%') return 1;
	return 0;
}
//test functions
void testIsStatement(char **arr);
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
int isStatement(char str[]){
	
	int ok = 0;
	int state = 0;
	char str1[256];
	
	int ends_with_semicolon = endsWithSemiColon(str);
	if(str[strlen(str)-1]==';'){
		str[strlen(str)-1] = '\0';
	}
	
	char* tok = strtok(str, " ");
	while(tok != NULL){
		
		switch(state){
			case 0: state = isIdentifier(tok) == 1 ? 1 : 7;
					ok = 1;
					break;
			case 1: state = strcmp(tok,"=") == 0 ? 2 : 7;
					ok = 1;
					break;
			case 2: if(tok[0] == '+' || tok[0] == '-' || strcmp(tok+1,"")!=0)	state = 3;
					else if(isIdentifier(tok))	state = 4;
					else if(isInteger(tok) ||isFloat(tok))	state = 5;
					else state = 7;
			case 3: if(isIdentifier(tok+1))	state = 4;
					else if(isInteger(tok) || isFloat(tok))	state = 5;
					else state = 7;
					ok = 0;
					break;
			case 4: if(ends_with_semicolon == 1) state = 6;
					else state = 7;
					break;
			case 5: if(ends_with_semicolon == 1) state=6;
					else state = 7;
					break;
			case 6: if(strtok(NULL," ") != NULL) state = 7;
					ok = 1;
					break;
			case 7: state = 7;
					ok = 1;
					break;
		}
		if(ok == 1) tok = strtok(NULL, " ");
	}
	
	return state==6;
}
void testIsStatement(char **arr){
	int i;
	char string[MAX_STRING_SIZE];
	printf("\n\n[Statements]Testing 5 Strings:\n");
	for(i=0; i<NUMBER_OF_STRING; i++){
		strcpy(string,arr[i]);
		printf("\n\t'%s'\n", string);
		if(isStatement(string) == 1){
			printf("\t\tValid Statement\n\n");
		}else printf("\t\tInvalid\n\n");
	}
}
void testAll(void){
	char *valid_statement_strings[5] = {"identifer = +positive;" , "_under = +100;" , "var =       spacez   ;", "num = ber;", "a = 1;"};
	char *invalid_statement_strings[5] = {" = ;" , "cit = number1" , "lets_go = wild cats;", "number = !1;", "num=+1;"};
	//Testing Statement Strings...
	testIsStatement(valid_statement_strings);
    testIsStatement(invalid_statement_strings);
    
}

