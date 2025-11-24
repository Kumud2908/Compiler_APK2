// Advanced Pointer Testcases for C Compiler
#include <stdio.h>

void testcase1();
void testcase2();
void testcase3();
void testcase4();
void testcase5();

int main() {
    printf("==== ADVANCED POINTER TESTCASES ====\n\n");
    
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    
    return 0;
}

// Testcase 1: Pointer arithmetic on 2D array
void testcase1() {
    printf("Testcase 1 (Pointer arithmetic on 2D array): ");
    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int *p = &a[0][0];
    p = p + 4;  // Should point to a[1][1] = 5
    printf("%d\n", *p);  // Expected: 5
}

// Testcase 2: Pointer to pointer update
void testcase2() {
    printf("Testcase 2 (Pointer to pointer update): ");
    int x = 10;
    int *p = &x;
    int **q = &p;
    **q = **q + 5;  // Modify x through double pointer
    printf("%d %d\n", x, **q);  // Expected: 15 15
}

// Testcase 3: Pointer to array
void testcase3() {
    printf("Testcase 3 (Array access through pointer): ");
    int arr[5] = {10,20,30,40,50};
    int *p = arr;
    printf("%d\n", *(p+3));  // Expected: 40
}

// Testcase 4: Pointer difference
void testcase4() {
    printf("Testcase 4 (Pointer difference): ");
    int arr[5] = {5,10,15,20,25};
    int *p = arr;
    int *q = arr + 4;
    int diff = q - p;
    printf("%d\n", diff);  // Expected: 4
}

// Testcase 5: Pointer aliasing
void testcase5() {
    printf("Testcase 5 (Pointer aliasing): ");
    int x = 5;
    int *p = &x;
    int *q = p;  // q is alias of p
    *q = 11;     // Modify through alias
    printf("%d %d %d\n", x, *p, *q);  // Expected: 11 11 11
}
