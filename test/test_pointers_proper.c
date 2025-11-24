// Comprehensive Pointer Testcases for C Compiler
// All tests use proper C syntax (no C++ features)
#include <stdio.h>

void testcase1();
void testcase2();
void testcase3();
void testcase4();
void testcase5();
void testcase6();
void testcase7();
void testcase8();

int main() {
    printf("==== COMPREHENSIVE POINTER TESTCASES ====\n\n");
    
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    testcase6();
    testcase7();
    testcase8();
    
    printf("\n==== ALL TESTS COMPLETED ====\n");
    return 0;
}

// Test 1: Pointer arithmetic on 2D array
void testcase1() {
    printf("Test 1 - Pointer arithmetic on 2D array:\n");
    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int *ptr = &a[0][0];
    
    printf("  a[0][0] = %d\n", *ptr);
    ptr = ptr + 4;  // Should point to a[1][1] = 5
    printf("  After ptr+4: %d (Expected: 5)\n", *ptr);
    ptr = ptr + 3;  // Should point to a[2][1] = 8
    printf("  After ptr+7 total: %d (Expected: 8)\n\n", *ptr);
}

// Test 2: Pointer-to-pointer (double indirection)
void testcase2() {
    printf("Test 2 - Pointer to pointer:\n");
    int x = 10;
    int *p1 = &x;
    int **p2 = &p1;
    
    printf("  x = %d\n", x);
    printf("  *p1 = %d\n", *p1);
    printf("  **p2 = %d\n", **p2);
    
    **p2 = **p2 + 5;  // Modify x through double pointer
    printf("  After **p2 += 5:\n");
    printf("  x = %d, **p2 = %d (Expected: 15, 15)\n\n", x, **p2);
}

// Test 3: Array access through pointer with arithmetic
void testcase3() {
    printf("Test 3 - Array access through pointer:\n");
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;
    
    printf("  arr[0] = %d\n", *ptr);
    printf("  arr[1] = %d\n", *(ptr + 1));
    printf("  arr[3] = %d (Expected: 40)\n", *(ptr + 3));
    printf("  arr[4] = %d (Expected: 50)\n\n", *(ptr + 4));
}

// Test 4: Pointer aliasing (multiple pointers to same location)
void testcase4() {
    printf("Test 4 - Pointer aliasing:\n");
    int value = 5;
    int *ptr1 = &value;
    int *ptr2 = ptr1;  // ptr2 is alias of ptr1
    
    printf("  Initial: value=%d, *ptr1=%d, *ptr2=%d\n", value, *ptr1, *ptr2);
    
    *ptr2 = 11;  // Modify through alias
    printf("  After *ptr2=11:\n");
    printf("  value=%d, *ptr1=%d, *ptr2=%d\n", value, *ptr1, *ptr2);
    printf("  (Expected: 11, 11, 11)\n\n");
}

// Test 5: Pointer swapping
void testcase5() {
    printf("Test 5 - Pointer swapping:\n");
    int a = 3;
    int b = 9;
    int *ptr_a = &a;
    int *ptr_b = &b;
    
    printf("  Before swap: *ptr_a=%d, *ptr_b=%d\n", *ptr_a, *ptr_b);
    
    // Swap pointer values, not addresses
    int temp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = temp;
    
    printf("  After value swap:\n");
    printf("  a=%d, b=%d (Expected: 9, 3)\n", a, b);
    printf("  *ptr_a=%d, *ptr_b=%d (Expected: 9, 3)\n\n", *ptr_a, *ptr_b);
}

// Test 6: Multiple pointer operations
void testcase6() {
    printf("Test 6 - Multiple pointer operations:\n");
    int arr[3] = {100, 200, 300};
    int *ptr = arr;
    
    printf("  First element: %d\n", *ptr);
    ptr++;
    printf("  After ptr++: %d (Expected: 200)\n", *ptr);
    ptr++;
    printf("  After ptr++: %d (Expected: 300)\n\n", *ptr);
}

// Test 7: Pointer with structs
void testcase7() {
    printf("Test 7 - Pointer with structs:\n");
    
    struct Point {
        int x;
        int y;
    };
    
    struct Point p1;
    p1.x = 10;
    p1.y = 20;
    
    struct Point *ptr = &p1;
    
    printf("  Using dot: p1.x=%d, p1.y=%d\n", p1.x, p1.y);
    printf("  Using arrow: ptr->x=%d, ptr->y=%d\n", ptr->x, ptr->y);
    
    ptr->x = 100;
    ptr->y = 200;
    
    printf("  After modification:\n");
    printf("  p1.x=%d, p1.y=%d (Expected: 100, 200)\n\n", p1.x, p1.y);
}

// Test 8: Pointer arithmetic with loops
void testcase8() {
    printf("Test 8 - Pointer arithmetic in loop:\n");
    
    int numbers[5] = {5, 10, 15, 20, 25};
    int *ptr = numbers;
    
    printf("  Array elements: ");
    int i;
    for (i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
    printf("  (Expected: 5 10 15 20 25)\n\n");
}
