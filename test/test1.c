// Test Case 1: All arithmetic/logical operators, if-else, for, while, do-while, switch, goto, break, continue, static keyword

#include <stdio.h>
using namespace std;

static int counter = 0;

int main() {
    int a = 5, b = 10;
    char c = 'x';

    // Arithmetic and logical operators
    int sum = a + b;
    int diff = a - b;
    int prod = a * b;
    int mod = b % a;
    int div = b / a;
    int logical = (a < b) && (b > 0) || !(a == b);

    // if-else
    if (sum > 10) {
        printf("Sum is greater than 10\n");
    } else {
        printf("Sum is less or equal to 10\n");
    }

    // for loop
    for (int i = 0; i < 3; i++) {
        printf("For loop iteration: %d\n", i);
    }

    // while loop
    while (counter < 2) {
        printf("While loop counter: %d\n", counter);
        counter++;
    }

    // do-while loop
    int dw = 0;
    do {
        printf("Do-while iteration: %d\n", dw);
        dw++;
    } while (dw < 2);

    // switch case
    int choice = 1;
    switch (choice) {
        case 0: printf("Choice 0\n"); break;
        case 1: printf("Choice 1\n"); break;
        default: printf("Default choice\n");
    }

    // goto, break, continue
    goto skip;
    printf("This will be skipped\n");
    skip:
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (i == 4) break;
        printf("Loop value: %d\n", i);
    }

    return 0;
}