#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Max number of characters on new line from file
#define LINE_MAX 1028

char expression[LINE_MAX];
int position;

char next();
char peek();
int E();
int EE(int i);
int A();
int AA(int i);
int B();
int BB(int i);
int C();

int main ( int argc, char *argv[] )
{
	char line[LINE_MAX];

	while (fgets(line, LINE_MAX, stdin) != NULL) {

		//remove the newline character for printing the expression
		size_t strlength = strlen(line);
		line[strlength-1] = '\0';

		//reset global variables
		position = 0;
		strcpy(expression, line);

		int result = E();

		printf("%s =  %x\n", line, result);
	}
}

char next(){
	return expression[position++];
}

char peek(){
	return expression[position];
}

int E(){
	int st = A();
	return EE(st);
}

//bitwise "|" OR
int EE(int i){
	char token = peek();

	if (token == '|'){ 
		next();
		int val = A();
		return EE(i | val);
	}else{
		return i; 
	}
}

int A(){
	int st = B();
	return AA(st);
}

//bitwise "^" XOR
int AA(int i){
	char token = peek();

	if (token == '^'){ 
		next();
		int val = B();
		return AA(i ^ val);
	}else{
		return i; 
	}
}

int B(){
	int st = C();
	return BB(st);
}

//bitwise "&" AND
int BB(int i){
	char token = peek();

	if (token == '&'){ 
		next();
		int val = C();
		return BB(i & val);
	}else{
		return i; 
	}
}

/*********************************************************************
 *********************************************************************
 This is the function I am having a problem with. Strtol is giving me 
 inconsistent integer values.
 *********************************************************************
 *********************************************************************/
int C(){ 

	char token = next(); 

	if(token == '<'){
		//bitwise shift secondToken <<
		printf("BITEWISE LEFT SHIFT: %c\n", token);
		return (C() << 1) & 15; //0xf;
	}else if(token == '>'){
		//bitwise shift secondToken >>
		return C() >> 1;
	}else if(token == '~'){
		//bitwise not secondToken ~
		printf("BITEWISE NOT: %c\n", token);
		return (~C()) & 15;
	}else if(token == '('){
		int val = E();
		next();
		return val; 
	}else{
		printf("TOKEN: %c\n", token);
		//return the token hex value as int
		char temp[1];
		temp[0] = token;
		printf("TEMP 0: %c\n", temp[0]);
		printf("TOKEN int: %d\n", (int)strtol(temp, NULL, 16) & 15);
		return (int)(strtol(temp, NULL, 16) & 15); //0xf;
	}
}

