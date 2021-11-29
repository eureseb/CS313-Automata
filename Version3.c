#include <stdio.h>
#include <string.h>
#define NUMBER_OF_STRING 5
#define MAX_STRING_SIZE 256

int isExpandedStatement(char string[]);
/*
		Expanded statement condition:
			Identifier =(e + (+) + (-)) (Identifier + Float/Integer)(;) + ( (e + (+) + (-))(Identifier + Float/Integer)(Operator))* (e + (+) + (-))(Identifier + Float/Integer)(;)
			
			1. Statement must start with valid identifier. Example "_num1 = num2;" is valid | "1num = num2;" is not
			2. After the '=' symbol, identifiers and numbers may be signed/unsigned. Example "num1 = +num1;" is valid.
			3. Statements must end in ';'.	Example "num1 = num2;" is valid | "num1 = num2" is not
			4. For signed numbers/identifiers, there should not be space after the sign. Example "num1 = num2 + -num3" is valid | "num1 = num2 + - num3" is not.
			5. Multiple spaces between identifiers, numbers, and symbols is ignored. Statements are accepted except if they break any of the conditions above. 
				"   num   = num1 +  num2    ;" is accepted. "num=num1+-num2;" is accepted. "num=num1+-num2;  " is not accepted. "num = num1 + - num2;  " is not accepted
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

//test function;
void testIsExpandedStatement(char **arr);
void testAll(void);
int main(){
	
	testAll();
	
	return 0;
}

int isExpandedStatement(char string[]){
	int state = 0;
	char c;
	int i = 0;
	while(string[i] != '\0'){
		c = string[i];
		switch(state){
			case 0: if(isalpha(c) != 0 || c=='_') 		state = 1;
					else if(isspace(c))					state = 0;
					else 								state = 16;
					break;
			case 1: if(isalpha(c) != 0 || 
						isdigit(c) != 0 || c=='_') 		state = 1;
					else if(c=='=') 					state = 3;
					else if(isspace(c)) 				state = 2;
					else state = 16;
					break;
			case 2: if(isspace(c))						state = 2;
					else if(c=='=') 					state = 3;
					else 							    state = 16;
					break;
			case 3: if(isspace(c))						state = 3;
					else if(c=='+'||c=='-')				state = 4;
					else if(isdigit(c) != 0) 			state = 5;
					else if(c=='.') 					state = 8;
					else if(isalpha(c) != 0 || c=='_')  state = 12;
					else 								state = 16;
					break;
			case 4: if(isdigit(c) != 0) 				state = 5;
					else if(c=='.') 					state = 8;
					else if(isalpha(c) || c=='_') 		state = 12;
					else state = 16;
					break;
			case 5: if(isdigit(c) != 0) 				state = 5;
					else if(isspace(c)) 				state = 6;
					else if(c==';') 					state = 7;
					else if(c=='.') 					state = 8;
					else if(isOper(c)) 					state = 15;
					else 								state = 16;
					break;
			case 6: if(isspace(c)) 						state = 6;
					else if(c==';') 					state = 7;
					else if(isOper(c)) 					state = 15;
					else 								state = 16;
					break;
			case 7: state = 16;	
					break;
			case 8: if(isdigit(c) != 0) 				state = 9;
					else 								state = 16;
					break;
			case 9: if(isdigit(c) != 0) 				state = 9;
					else if(isspace(c)) 				state = 10;
					else if(c==';') 					state = 11;
					else if(isOper(c)) 					state = 15;
					else state = 16;
					break;
			case 10:if(isspace(c)) 						state = 10;
					else if(c==';')						state = 11;
					else if(isOper(c)) 					state = 15;
					else 								state = 16;
					break;
			case 11:state = 16;
					break;
			case 12:if(isalpha(c) != 0 || 
						isdigit(c) != 0 || c=='_') 		state = 12;
					else if(isspace(c)) 				state = 13;
					else if(c==';') 					state = 14;
					else if(isOper(c)) 					state = 15;
					else 								state = 16;
					break;
			case 13:if(isspace(c)) 						state = 13;
					else if(c==';') 					state = 14;
					else if(isOper(c)) 					state = 15;
					else 								state = 16;
					break;
			case 14:state = 16;
					break;
			case 15:if(c=='+' || c=='-') 				state = 4;
					else if(isdigit(c) != 0) 			state = 5;
					else if(c=='.') 					state = 8;
					else if(isalpha(c) || c=='_') 		state = 12;
					else if(isspace(c))					state = 15;
					else state = 16;
					break;
			case 16:state = 16;
					break;
		}
		//printf("state = %d char = %c\n",state,c);
		i++;
	}
	
    int flag = state == 7 || state == 11 || state == 14;
    	
	return flag;
}

void testIsExpandedStatement(char **arr){
	int i;
	char string[MAX_STRING_SIZE];
	printf("\n\n[Expanded Statements]Testing 5 Strings:\n");
	for(i=0; i<NUMBER_OF_STRING; i++){
		strcpy(string,arr[i]);
		printf("\n\t'%s'\n", string);
		if(isExpandedStatement(string) == 1){
			printf("\t\tValid Expanded Statement\n\n");
		}else printf("\t\tInvalid Statement\n\n");
	}
}
void testAll(void){
	char *valid_expanded_statement_strings[5] = {"identifer = negative - +positive;" , "no=spaces--in+between;" , "covid_protocol = 6   *   spaces   /   apart      ;", "_under = int + 2;", "simple = assignment;"};
	char *invalid_expanded_statement_strings[5] = {"var = 2 + - 2;" , "var = *operator;" , "snake_case = mouse + mice", "!number = !1;", "num = + 1 + 1;"};

    //Testing Expanded Statement Strings...
    testIsExpandedStatement(valid_expanded_statement_strings);
    testIsExpandedStatement(invalid_expanded_statement_strings);
}
	
/*
	This version is buggy.
int isExpandedStatement(char str[]){
	int ok = 0;
	int state = 0;
	char str1[256];
	
	int ends_with_semicolon = endsWithSemiColon(str);
	printf("Ends with semicolon : %d\n",ends_with_semicolon);
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
			case 2: if(tok[0] == '+' || tok[0] == '-')	{ state = 3;
					 ok = strtok(NULL, " ") == NULL ? 1 : 0;
					}
					else if(isIdentifier(tok))	{ state = 4;
					 ok = strtok(NULL, " ") == NULL ? 1 : 0;
					}
					else if(isInteger(tok) ||isFloat(tok))	{ state = 5;
					 ok = strtok(NULL, " ") == NULL ? 1 : 0;
					}
					else state = 7;
					break;
			case 3: if(isIdentifier(tok+1))	state = 4;
					else if(isInteger(tok) || isFloat(tok))	state = 5;
					else state = 7;
					ok = 1;
					break;
			case 4: if(strlen(tok)==1 && isOper(tok[0])) state = 2;
					else if(ends_with_semicolon == 1) state = 6;
					else state = 7;
					ok = 1;
					break;
			case 5: if(strlen(tok)==1 && isOper(tok[0])) state = 2;
					else if(ends_with_semicolon == 1) state=6;
					else state = 7;
					break;
			case 6: if(strtok(NULL," ") != NULL) state = 7;
					ok = 1;
					break;
			case 7: state = 7;
					ok = 1;
					break;
		}
		printf("state: %d strlen(tok)=%d isOpen(tok[0])=%d tok=%s \n",state,strlen(tok),isOper(tok[0]),tok);
		if(ok == 1) tok = strtok(NULL, " ");
	}
	return state;
} 
*/
