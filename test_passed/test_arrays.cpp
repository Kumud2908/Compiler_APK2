#include <stdio.h>

int main() {
    // Test 1: Array declaration and access
    int arr[10];
    arr[5] = 10;  // OK
    
    // Test 2: Multi-dimensional arrays
    int matrix[3][4];
    matrix[1][2] = 5;  // OK
    
    // Test 3: Array index must be integer
    int idx = 2;
    arr[idx] = 20;  // OK
    
    float f_idx = 2.5;
    arr[f_idx] = 30;  // ERROR: Array index must be integer
    
    // Test 4: Too many dimensions
     matrix[1][2][3] = 5;  // ERROR: Too many subscripts
    
    // Test 5: Array bounds (if implementing constant checking)
     arr[15] = 100;  // WARNING: Index out of bounds
    
    return 0;
}