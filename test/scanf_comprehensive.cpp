#include <stdio.h>

// =============================
// TESTCASE 1: scanf with integer
// =============================
void testcase1() {
    int num;
    
    printf("\nTESTCASE 1: scanf with integer\n");
    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("You entered: %d\n", num);
}

// =============================
// TESTCASE 2: scanf with multiple integers
// =============================
void testcase2() {
    int a, b, c;
    
    printf("\nTESTCASE 2: scanf with multiple integers\n");
    printf("Enter three integers: ");
    scanf("%d %d %d", &a, &b, &c);
    printf("You entered: %d, %d, %d\n", a, b, c);
}

// =============================
// TESTCASE 3: scanf with float
// =============================
void testcase3() {
    float f;
    
    printf("\nTESTCASE 3: scanf with float\n");
    printf("Enter a float: ");
    scanf("%f", &f);
    printf("You entered: %f\n", f);
}

// =============================
// TESTCASE 4: scanf with character
// =============================
void testcase4() {
    char ch;
    
    printf("\nTESTCASE 4: scanf with character\n");
    printf("Enter a character: ");
    scanf("%c", &ch);
    printf("You entered: %c\n", ch);
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
// TESTCASE 6: scanf in expression
// =============================
void testcase6() {
    int num1, num2;
    
    printf("\nTESTCASE 6: scanf with calculation\n");
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    int sum = num1 + num2;
    printf("Sum: %d + %d = %d\n", num1, num2, sum);
}

// =============================
// TESTCASE 7: scanf in loop
// =============================
void testcase7() {
    int nums[3];
    
    printf("\nTESTCASE 7: scanf in loop\n");
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
// TESTCASE 8: scanf with array element
// =============================
void testcase8() {
    int arr[5];
    
    printf("\nTESTCASE 8: scanf with array\n");
    printf("Enter value for arr[2]: ");
    scanf("%d", &arr[2]);
    printf("arr[2] = %d\n", arr[2]);
}

// =============================
// MAIN (For manual testing)
// =============================
int main() {
    printf("=================================\n");
    printf("SCANF FUNCTIONALITY TEST\n");
    printf("=================================\n");
    printf("Note: This tests compilation.\n");
    printf("Actual input testing requires interactive mode.\n");
    
    // Uncomment individual tests as needed:
    // testcase1();
    // testcase2();
    // testcase3();
    // testcase4();
    // testcase5();
    // testcase6();
    // testcase7();
    // testcase8();
    
    printf("\nAll scanf testcases compiled successfully!\n");
    return 0;
}
