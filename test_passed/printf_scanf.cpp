#include <stdio.h>

// =============================
// TESTCASE 1: printf basic types
// =============================
void testcase1() {
    int i = 42;
    float f = 3;
    char c = 'A';
    
    printf("\nTESTCASE 1: printf basic types\n");
    printf("Integer: %d\n", i);
    printf("Float: %f\n", f);
    printf("Character: %c\n", c);
}

// =============================
// TESTCASE 2: printf with multiple values
// =============================
void testcase2() {
    int a = 10;
    int b = 20;
    int sum = a + b;
    
    printf("\nTESTCASE 2: printf multiple values\n");
    printf("%d + %d = %d\n", a, b, sum);
}

// =============================
// TESTCASE 3: scanf with integer
// =============================
void testcase3() {
    int num;
    
    printf("\nTESTCASE 3: scanf with integer\n");
    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("You entered: %d\n", num);
}

// =============================
// TESTCASE 4: scanf with multiple integers
// =============================
void testcase4() {
    int a, b, c;
    
    printf("\nTESTCASE 4: scanf multiple integers\n");
    printf("Enter three integers: ");
    scanf("%d %d %d", &a, &b, &c);
    printf("You entered: %d, %d, %d\n", a, b, c);
}

// =============================
// TESTCASE 5: scanf with pointer
// =============================
void testcase5() {
    int x;
    int* ptr = &x;
    
    printf("\nTESTCASE 5: scanf with pointer\n");
    printf("Enter value via pointer: ");
    scanf("%d", ptr);
    printf("Value: %d\n", *ptr);
}

// =============================
// TESTCASE 6: scanf in loop
// =============================
void testcase6() {
    int nums[3];
    
    printf("\nTESTCASE 6: scanf in loop\n");
    printf("Enter 3 numbers:\n");
    
    for (int i = 0; i < 3; i++) {
        printf("Number %d: ", i + 1);
        scanf("%d", &nums[i]);
    }
    
    printf("You entered: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

// =============================
// MAIN
// =============================
int main() {
    printf("=================================\n");
    printf("PRINTF/SCANF TEST SUITE\n");
    printf("=================================\n");
    
    testcase1();
    testcase2();
    
    // Uncomment for interactive testing:
    // testcase3();
    // testcase4();
    // testcase5();
    // testcase6();
    
    printf("\nAll printf/scanf tests completed!\n");
    return 0;
}