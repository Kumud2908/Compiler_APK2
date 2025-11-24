#include <stdio.h>

void testcase1() {
    printf("\nTESTCASE 1: Simple if-else\n");
    int x = 10;
    if (x > 5)
        printf("x > 5 (TRUE)\n");
    else
        printf("x <= 5 (FALSE)\n");
}

void testcase2() {
    printf("\nTESTCASE 2: Nested if-else\n");
    int a = 20;
    if (a > 0) {
        if (a % 2 == 0)
            printf("a is positive and even\n");
        else
            printf("a is positive and odd\n");
    } else {
        printf("a is zero or negative\n");
    }
}

void testcase3() {
    printf("\nTESTCASE 3: If-else ladder\n");
    int marks = 72;
    if (marks >= 90)
        printf("Grade A\n");
    else if (marks >= 75)
        printf("Grade B\n");
    else if (marks >= 50)
        printf("Grade C\n");
    else
        printf("Fail\n");
}

void testcase4() {
    printf("\nTESTCASE 4: Logical operators\n");
    int x = 10, y = 20;

    if (x > 5 && y > 15)
        printf("Both conditions TRUE\n");
    else
        printf("Condition FALSE\n");
}

void testcase5() {
    printf("\nTESTCASE 5: Multiple relational operators\n");
    int n = 15;

    if (n > 10 && n < 20)
        printf("n is between 10 and 20\n");
    else
        printf("n is NOT between 10 and 20\n");
}

void testcase6() {
    printf("\nTESTCASE 6: Using NOT operator\n");
    int flag = 0;

    if (!flag)
        printf("flag is FALSE\n");
    else
        printf("flag is TRUE\n");
}

void testcase7() {
    printf("\nTESTCASE 7: Complex expression\n");
    int x = 5, y = 3;

    if ((x + y * 2) == 11)
        printf("(x + y * 2) == 11 TRUE\n");
    else
        printf("(x + y * 2) == 11 FALSE\n");
}

void testcase8() {
    printf("\nTESTCASE 8: If without braces\n");
    int a = 10;

    if (a > 5)
        if (a < 15)
            printf("a > 5 and a < 15\n");
        else
            printf("Inner else\n");
    else
        printf("Outer else\n");
}

void testcase9() {
    printf("\nTESTCASE 9: Dangling else behavior\n");
    int x = 4;

    if (x > 3)
        if (x > 10)
            printf("x > 10\n");
        else
            printf("else belongs to inner if\n");
}

void testcase10() {
    printf("\nTESTCASE 10: Comparing characters\n");
    char c = 'a';

    if (c == 'a')
        printf("c is 'a'\n");
    else
        printf("c is not 'a'\n");
}

void testcase11() {
    printf("\nTESTCASE 11: String comparison WRONG way\n");
    char s1[] = "hello";

    if (s1 == "hello")
        printf("WRONG: This will never be true\n");
    else
        printf("Correct behavior: use strcmp instead\n");
}

void testcase12() {
    printf("\nTESTCASE 12: Integer overflow behavior\n");
    int x = 2147483647; // max int

    if (x + 1 < x)
        printf("Overflow occurred (TRUE)\n");
    else
        printf("Overflow didn't occur (FALSE?)\n");
}

void testcase13() {
    printf("\nTESTCASE 13: Floating point precision issues\n");
    float a = 0.1 * 3;

    if (a == 0.3)
        printf("Equal (unexpected)\n");
    else
        printf("Not equal due to float precision\n");
}

void testcase14() {
    printf("\nTESTCASE 14: If with assignment vs comparison\n");
    int x = 0;

    if (x = 5)  // assignment, NOT comparison
        printf("x=5 makes condition TRUE\n");
    else
        printf("FALSE\n");
}

int main() {
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    testcase6();
    testcase7();
    testcase8();
    testcase9();
    testcase10();
    testcase11();
    testcase12();
    testcase13();
    testcase14();
    return 0;
}
