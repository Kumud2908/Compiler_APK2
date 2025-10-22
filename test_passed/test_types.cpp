#include <stdio.h>

int main() {
    // Test 1: Implicit type conversion warning
    int i = 10;
    float f = i;  // WARNING: Implicit conversion
    
    // Test 2: Pointer to different types
    int *ip;
    float *fp;
    ip = fp;  // ERROR: Incompatible pointer types
    
    // Test 3: Address-of operator on non-lvalue
    int *bad = &5;  // ERROR: & requires lvalue
    
    // Test 4: Dereference non-pointer
    int x = 5;
    int y = *x;  // ERROR: Cannot dereference non-pointer type
    
    // Test 5: Increment/decrement on non-numeric
    int *ptr;
    ptr++;  // OK - pointer increment
    
    return 0;
}