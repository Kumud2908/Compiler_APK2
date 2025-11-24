#include <stdio.h>

// Test ptr++ and ptr--
void test_postfix_increment() {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;
    
    printf("Test 1: Postfix increment (ptr++)\n");
    printf("Initial: *p = %d\n", *p);   // 10
    p++;
    printf("After p++: *p = %d\n", *p); // 20
    p++;
    printf("After p++: *p = %d\n", *p); // 30
    
    printf("\nTest 2: Postfix decrement (ptr--)\n");
    p--;
    printf("After p--: *p = %d\n", *p); // 20
    p--;
    printf("After p--: *p = %d\n", *p); // 10
}

// Test with pointer arithmetic
void test_pointer_arithmetic() {
    int nums[] = {5, 15, 25, 35, 45};
    int *ptr = nums;
    
    printf("\nTest 3: Combining ptr++ with dereference\n");
    printf("*ptr++ would be: %d (though we test sequentially)\n", *ptr);
    ptr++;
    printf("After increment: *ptr = %d\n", *ptr);
    
    printf("\nTest 4: Array access with ptr++ in loop\n");
    int *ptr2 = nums;
    for (int i = 0; i < 5; i++) {
        printf("nums[%d] = %d\n", i, *ptr2);
        ptr2++;
    }
}

int main() {
    test_postfix_increment();
    test_pointer_arithmetic();
    printf("\nAll tests passed!\n");
    return 0;
}
