#include <stdio.h>

int isIdentifier(char string[]);
int isInteger(char string[]);
int isFloat(char string[]);
int isStatement(char string[]);

int main(){
	int res;// = isIdentifier("1a");
	res = isStatement("num1 = 10a;");
	printf("%d", res);
	return 0;
}
int isIdentifier(char string[]){
	int state = 0;
	char c;
	int i = 0;
	while(state!=2 && string[i] != '\0'){
		c = string[i];//storing current char.
		
		switch(state){
			case 0: if((c <= 'z' && c >= 'a') || (c <= 'Z' && c>= 'A') || c=='_') state = 1;// if current char is a-z or A-Z or an underscore
					else state = 2;
					break;
			case 1: if((c <= 'z' && c >= 'a') || (c <= 'Z' && c>= 'A') || c=='_' || (c <= '9' && c>= '0')) state = 1;// if current char is a-z, A-Z, 0-9, an underscore
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
	while(state!=1 && string[i] != '\0'){
		c = string[i];//storing current char.
		
		switch(state){
			case 0: if(c <= '9' && c>= '0') state = 2;
					else if(c=='+' || c=='-') state = 3;
					else state = 1;
					break;
			case 1:	state = 1;
					break;
			case 2: if(c <= '9' && c>= '0') state = 2;
					else state = 1;
					break;
			case 3: if(c <= '9' && c>= '0') state = 2;
					break;
		}
		i++;
	}
	return state==2;
}
int isFloat(char string[]){
	int state = 0;
	char c;
	int i = 0;
	while(state!=1 && string[i] != '\0'){
		c = string[i];//storing current char.
		
		switch(state){
			case 0: if(c <= '9' && c>= '0' || c=='+' || c=='-') state = 2;
					else if(c=='.') state = 3;
					else state = 1;
					break;
			case 1:	state = 1;
					break;
			case 2: if(c <= '9' && c>= '0') state = 2;
					else if(c=='.') state = 3;
					else state = 1;
					break;
			case 3: if(c <= '9' && c>= '0') state = 4;
					else state = 1;
					break;
			case 4: if(c <= '9' && c>= '0') state = 4;
					else state = 1;
					break;
		}
		i++;
	}
	return state==4 || state== 2;// 2 final states
}
int isStatement(char string[]){
	int state = 0;
	char c;
	int i = 0;
	while(state!=2 && string[i] != '\0'){
		c = string[i];//storing current char.
		
		switch(state){
			case 0: if((c <= 'z' && c >= 'a') || (c <= 'Z' && c>= 'A') || c=='_') state = 1;// if current char is a-z or A-Z or an underscore
					else state = 2;
					break;
			case 1: if((c <= 'z' && c >= 'a') || (c <= 'Z' && c>= 'A') || c=='_' || (c <= '9' && c>= '0' || c==' ')) state = 1;// if current char is a-z, A-Z, 0-9, an underscore
					else if(c=='=') state = 3;
					else state = 2;
					break;
			case 2: state = 2;
					break;
			case 3: if((c <= 'z' && c >= 'a') || (c <= 'Z' && c>= 'A') || c=='_' || c==' ') state = 4;// if current char is a-z or A-Z or an underscore
					else if(c <= '9' && c>= '0') state = 5;
					else if(c=='+' || c=='-') state = 6;
					else if(c=='.') state = 7;
					else state = 2;
					break;
			case 4: if((c <= 'z' && c >= 'a') || (c <= 'Z' && c>= 'A') || c=='_' || (c <= '9' && c>= '0')) state = 4;
					else if(c==';') state = 8;
					else state = 2;
					break;
			case 5: if(c <= '9' && c>= '0') state = 5;
					else if(c=='.') state = 7;
					else if(c==';') state = 9;
					else state = 2;
					break;
			case 6: if((c <= 'z' && c >= 'a') || (c <= 'Z' && c>= 'A') || c=='_') state = 4;
					else if(c <= '9' && c>= '0') state = 5;
					else if(c=='.') state = 7;
					else state = 2;
					break;
			case 7: if(c <= '9' && c>= '0') state = 10;
					else state = 2;
					break;
			case 8: state = 2;
					break;
			case 9: state = 2;
					break;
			case 10:if(c <= '9' && c>= '0') state = 10;
					else if(c==';') state = 11;
					else state = 2;
					break;
			case 11:state = 2;
					break;
		}
		i++;
	}
	int flag = state == 8 || state == 9 || state == 11;
	return flag;
}
