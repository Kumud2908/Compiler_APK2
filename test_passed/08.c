/* 
 * Feature: Syntax Error Test
 * File   : syntax_error_test.c
 * Desc   : Program intentionally contains syntax errors for testing
 */

#include <stdio.h>

int main() {
    int a = 10
    printf("Value of a is %d\n", a); // Missing semicolon above will cause syntax error

    if (a > 5 {                       // Missing closing parenthesis
        printf("A is greater than 5\n");
    }

    return 0;
}