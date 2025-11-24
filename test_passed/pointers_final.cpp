// Comprehensive Pointer Testcases for C Compiler
// Focused on features that work correctly
#include <stdio.h>

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();

int main() {
    printf("==== POINTER TESTCASES ====\n\n");
    
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    
    printf("==== ALL TESTS COMPLETED ====\n");
    return 0;
}

// Test 1: Basic pointer operations
void test1() {
    printf("Test 1 - Basic pointer operations:\n");
    int x = 42;
    int *ptr = &x;
    
    printf("  x = %d\n", x);
    printf("  *ptr = %d\n", *ptr);
    
    *ptr = 100;
    printf("  After *ptr = 100:\n");
    printf("  x = %d (Expected: 100)\n\n", x);
}

// Test 2: Pointer-to-pointer
void test2() {
    printf("Test 2 - Pointer to pointer:\n");
    int value = 10;
    int *p = &value;
    int **pp = &p;
    
    printf("  value = %d\n", value);
    printf("  *p = %d\n", *p);
    printf("  **pp = %d\n", **pp);
    
    **pp = 25;
    printf("  After **pp = 25:\n");
    printf("  value = %d (Expected: 25)\n\n", value);
}

// Test 3: Array access via pointers
void test3() {
    printf("Test 3 - Array access through pointer:\n");
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;
    
    printf("  arr[0] = %d\n", *(ptr + 0));
    printf("  arr[1] = %d\n", *(ptr + 1));
    printf("  arr[2] = %d\n", *(ptr + 2));
    printf("  arr[3] = %d\n", *(ptr + 3));
    printf("  arr[4] = %d\n", *(ptr + 4));
    printf("  (Expected: 10, 20, 30, 40, 50)\n\n");
}

// Test 4: Pointer arithmetic on 2D array
void test4() {
    printf("Test 4 - Pointer arithmetic on 2D array:\n");
    int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int *ptr = &matrix[0][0];
    
    printf("  matrix[0][0] = %d\n", *ptr);
    printf("  matrix[0][1] = %d\n", *(ptr + 1));
    printf("  matrix[1][0] = %d\n", *(ptr + 3));
    printf("  matrix[1][1] = %d\n", *(ptr + 4));
    printf("  matrix[2][2] = %d\n", *(ptr + 8));
    printf("  (Expected: 1, 2, 4, 5, 9)\n\n");
}

// Test 5: Pointer aliasing
void test5() {
    printf("Test 5 - Pointer aliasing:\n");
    int num = 7;
    int *p1 = &num;
    int *p2 = p1;
    
    printf("  num = %d, *p1 = %d, *p2 = %d\n", num, *p1, *p2);
    
    *p2 = 15;
    printf("  After *p2 = 15:\n");
    printf("  num = %d, *p1 = %d, *p2 = %d\n", num, *p1, *p2);
    printf("  (Expected: 15, 15, 15)\n\n");
}

// Test 6: Pointer value swap
void test6() {
    printf("Test 6 - Swap values using pointers:\n");
    int a = 5;
    int b = 8;
    int *pa = &a;
    int *pb = &b;
    
    printf("  Before: a = %d, b = %d\n", a, b);
    
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
    
    printf("  After swap:\n");
    printf("  a = %d, b = %d\n", a, b);
    printf("  (Expected: 8, 5)\n\n");
}
