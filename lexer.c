/*
 * COMP 451 - Compiler Construction
 * Project Task 1: Lexical Analyzer (Lexer)
 * 
 * Scans an arithmetic expression and identifies tokens.
 * Valid tokens: lowercase single-letter identifiers, +, -, *, /
 * Sentinel: $
 * Invalid: anything else
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_OPERANDS 5

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        fprintf(stderr, "Example: %s a+b*c$\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    int len = strlen(input);

    /* Verify the expression ends with $ */
    if (input[len - 1] != '$') {
        fprintf(stderr, "Error: Expression must end with sentinel value '$'\n");
        return 1;
    }

    printf("Program finds following tokens in the expression:\n");
    printf("Expression received: %s\n", input);

    int operand_count = 0;

    for (int i = 0; i < len; i++) {
        char ch = input[i];

        if (ch == '$') {
            /* Sentinel reached — stop scanning */
            break;
        } else if (islower(ch)) {
            /* Single lowercase letter = identifier */
            if (operand_count >= MAX_OPERANDS) {
                printf("Error: Maximum of %d operands exceeded.\n", MAX_OPERANDS);
                return 1;
            }
            printf("int literal found: %c\n", ch);
            operand_count++;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            /* Arithmetic operator */
            printf("Arithmetic operator: %c\n", ch);
        } else {
            /* Anything else is invalid */
            printf("Invalid token encountered. Program terminated prematurely.\n");
            return 1;
        }
    }

    return 0;
}
