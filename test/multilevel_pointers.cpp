#include <stdio.h>

int main() {
    int x = 42;
    int *p = &x;
    int **pp = &p;
    int ***ppp = &pp;
    
    // Test 1: Single pointer
    printf("Test 1: Single pointer\n");
    printf("x = %d\n", x);
    printf("*p = %d\n", *p);
    printf("\n");
    
    // Test 2: Double pointer
    printf("Test 2: Double pointer\n");
    printf("**pp = %d\n", **pp);
    printf("\n");
    
    // Test 3: Triple pointer
    printf("Test 3: Triple pointer\n");
    printf("***ppp = %d\n", ***ppp);
    printf("\n");
    
    // Test 4: Modify through double pointer
    printf("Test 4: Modify through double pointer\n");
    **pp = 100;
    printf("After **pp = 100:\n");
    printf("x = %d\n", x);
    printf("*p = %d\n", *p);
    printf("**pp = %d\n", **pp);
    printf("\n");
    
    // Test 5: Modify through triple pointer
    printf("Test 5: Modify through triple pointer\n");
    ***ppp = 200;
    printf("After ***ppp = 200:\n");
    printf("x = %d\n", x);
    printf("*p = %d\n", *p);
    printf("**pp = %d\n", **pp);
    printf("***ppp = %d\n", ***ppp);
    printf("\n");
    
    // Test 6: Multiple variables with double pointers
    printf("Test 6: Multiple variables\n");
    int a = 10;
    int b = 20;
    int c = 30;
    
    int *p1 = &a;
    int *p2 = &b;
    int *p3 = &c;
    
    int **pp1 = &p1;
    
    printf("**pp1 = %d (points to a)\n", **pp1);
    
    pp1 = &p2;
    printf("**pp1 = %d (now points to b)\n", **pp1);
    
    pp1 = &p3;
    printf("**pp1 = %d (now points to c)\n", **pp1);
    printf("\n");
    
    // Test 7: Array of pointers with double pointer
    printf("Test 7: Array of pointers\n");
    int val1 = 11;
    int val2 = 22;
    int val3 = 33;
    
    int *ptrArr[3];
    ptrArr[0] = &val1;
    ptrArr[1] = &val2;
    ptrArr[2] = &val3;
    
    int **pArr = ptrArr;
    
    printf("*pArr[0] = %d\n", *pArr[0]);
    printf("*pArr[1] = %d\n", *pArr[1]);
    printf("*pArr[2] = %d\n", *pArr[2]);
    printf("\n");
    
    // Test 8: Pointer reassignment
    printf("Test 8: Pointer reassignment\n");
    int m = 50;
    int n = 60;
    int *pm = &m;
    int *pn = &n;
    int **ppm = &pm;
    
    printf("Before: **ppm = %d\n", **ppm);
    
    *ppm = pn;
    printf("After *ppm = pn: **ppm = %d\n", **ppm);
    printf("\n");
    
    return 0;
}
