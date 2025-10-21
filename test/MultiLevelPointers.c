#include <stdio.h>
// int main(){
// int a = 10;
// int *p = &a;
// int **q = &p;
// **q = 20;      // modifies a

// float x = 3.5;
// float *px = &x;
// *px = 4.2;
// return 0;
// }

// //invalid 
int main(){
    int *p;
*p = 5;          // dereference of uninitialized pointer

int **q;
*q = 10;         // assigning int to pointer-to-pointer

int a;
int *b = a;      // assigning int to pointer (missing &)
return 0;
}