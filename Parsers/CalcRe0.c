#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


#define SIZE 1024


int64_t evaluate_expression(char **buffer_ptr);
int64_t parse_factor(char **buffer_ptr);
int64_t parse_term(char **buffer_ptr);

void skip_whitespace(char **buffer_ptr) {
    while (isspace(**buffer_ptr)) {
        (*buffer_ptr)++;
    }
}

int64_t parse_factor(char **buffer_ptr) {
    skip_whitespace(buffer_ptr); // Skip any whitespace before the factor

    int64_t value;

    if (**buffer_ptr == '(') {
        (*buffer_ptr)++;
        
        value = evaluate_expression(buffer_ptr); 
        skip_whitespace(buffer_ptr);

        if (**buffer_ptr != ')') {
            fprintf(stderr, "Error: Mismatched parentheses - Expected ')'\n");
            exit(EXIT_FAILURE); 
        }
        (*buffer_ptr)++; 
    } else if (isdigit(**buffer_ptr) || (**buffer_ptr == '-' && isdigit(*(*buffer_ptr + 1)))) {
       value = strtoll(*buffer_ptr, buffer_ptr, 10);
    } else {
        fprintf(stderr, "Error: Unexpected character '%c' in factor\n", **buffer_ptr);
        exit(EXIT_FAILURE);
    }
    return value;
}


int64_t evaluate_expression(char **buffer_ptr) {
    int64_t result = parse_term(buffer_ptr); // Get the first term (number or parenthesized expression)
    // Loop to handle subsequent additions and subtractions
    while (**buffer_ptr != '\0') {
        skip_whitespace(buffer_ptr); // Skip whitespace before operator

        char op = **buffer_ptr;

        if (op == '+' || op == '-') {
            (*buffer_ptr)++; // Consume the operator
            int64_t next_factor = parse_term(buffer_ptr); // Get the next term

            if (op == '+') {
                result += next_factor;
            } else {
                result -= next_factor;
            }
        } else if (op == '*' || op== '-') {
            (*buffer_ptr)++;
            skip_whitespace(buffer_ptr); 
           int64_t next_term = parse_term(buffer_ptr);
           
        } else if (op == '.') {
            puts("No decimals allowed");
            exit(EXIT_FAILURE);
        } 

        else if (op == ')') {
            break;
        } else {
            break; // Stop parsing this level
        }
    }
    return result;
}

// Main parsing entry point
void parse(char *input_string) {
    char *current_buffer = input_string; // Create a mutable copy of the pointer
    int64_t final_result = evaluate_expression(&current_buffer);

    // After evaluation, check if there's any unparsed junk at the end
    skip_whitespace(&current_buffer);
    

    printf("Result: %ld\n", final_result);
}

 int64_t parse_term(char **buffer_ptr) {
    int64_t result = parse_factor(buffer_ptr);

    while (**buffer_ptr != '\0') {
        skip_whitespace(buffer_ptr);
        char op = **buffer_ptr;

        if (op == '*' || op == '/') {
            (*buffer_ptr)++; 
            skip_whitespace(buffer_ptr); 

            
            int64_t next_factor = parse_factor(buffer_ptr);

            if (op == '*') {
                result *= next_factor;
            } else {
                if (next_factor == 0) {
                    fprintf(stderr, "Error: Division by zero\n");
                    exit(EXIT_FAILURE);
                }
                result /= next_factor;
            }
        } else {
           //Job is done
            break;
        }
    }
    return result;
}

int main(void) {
 char buf[SIZE];
 //int64_t result=0;

 puts("Welcome to the integer calculator, insert here your query");

	if (fgets(buf, sizeof(buf), stdin)!= NULL) {
		parse(buf);
	} else {
			puts("STDIN error");
			return 1;
	}
  return 0;
}

