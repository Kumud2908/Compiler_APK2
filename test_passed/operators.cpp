#include <stdio.h>
// int main() {
//     int a = 10, b = 3;
//     float x = 2.5, y = 4.0;
    
//     int sum = a + b;
//     int diff = a - b;
//     int prod = a * b;
//     int quot = a / b;
//     int rem  = a % b;

//     float fsum = x + y;
//     float mix  = a + x;   // mixed int-float operation
//     float divf = y / b;

//     return 0;
// }

int main() {
    int a = 5, b = 10, c = 15;
    float x = 1.5, y = 2.5;

    float res = ((a + b) * (x - y) / (c >> 1)) + ((b & c) | (a ^ 3)) && (x > y);
    return 0;
}