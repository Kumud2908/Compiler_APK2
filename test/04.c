

#include <stdio.h>



int main() {
int arr[3][4];
arr[2] = 5;          // missing one index
arr[1][2][3] = 10;   // too many indices
arr[1.5][2] = 5;     // non-integer index
return 0;
}