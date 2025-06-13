#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define SIZE 1024

typedef enum {
	integer,
	floatingP,
	minus,
	plus,
	lparen,
	rparen,
	star,
	divide,
} TokenType;



void parse(char *);

int calculate(char *);


int parse_and_calculate(char *buffer) {
	bool sign = 1; //set to positive
	int64_t number=0;
	
while (*buffer != '\0') {
	if (isspace(*buffer)) {
				buffer++;
				continue;
			}
	else if (*buffer =='+') {
		sign = 1;
		buffer++;
	}

	else if (*buffer =='-') {
		sign = 0;
		buffer++;
	}
	else if (*buffer =='*') {
		buffer++;
	}
	else if (*buffer =='/') {
		buffer++;
	}
	else if (isdigit(*buffer)) {
		if (sign)
			number+=(int)strtol(buffer, &buffer, 10);
		if (!sign)
			number-=(int)strtol(buffer, &buffer, 10);
	}	

	}
return number;
		
	}

int parenthesis_op(char *buffer) {
	int number=0;
	int parent_count=0;
	while(*buffer!=')' && parent_count!=0) {
	

	}
return 0; //only here to avoid compiler warnings
}








int main(void) {
 char buf[SIZE];
 int64_t result=0;

 puts("Welcome to the integer calculator, insert here your query");

	if (fgets(buf, sizeof(buf), stdin)!= NULL) {
		result = parse_and_calculate(buf);

		printf("The result is: %ld\n", result);



	} else {
			puts("STDIN error");
			return 1;
	} 




}
