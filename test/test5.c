// Test Case 5: Lexical error detection (invalid symbols, malformed identifiers)

#include <stdio.h>

int main() {
    int a = 5;
    int 9invalidVar = 10;  // Invalid identifier (starts with number)
    float b = 3.14$;       // Invalid character '$'
    char c = '@';          // '@' may be unknown in your lexer rules

    printf("Values: %d %f %c\n", a, b, c);

    return 0;
}