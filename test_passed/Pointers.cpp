// #include <stdio.h>


// class Point {
//     int x, y;
//     void set(int a, int b) {
//         x = a;
//         y = b;
//     }
//     int sum() {
//         return x + y;
//     }
// };
// int main(){
//     Point p;
// p.set(2, 3);
// int s = p.sum();

// }

#include <bits/stdc++.h>
using namespace std;

// Testcase function declarations
void testcase1();
void testcase2();
void testcase3();
void testcase4();
void testcase5();
void testcase6();
void testcase7();
void testcase8();
void testcase9();
void testcase10();
void testcase11();
void testcase12();
void testcase13();
void testcase14();
void testcase15();

int main() {
    cout << "==== COMPLEX POINTER TESTCASES ====\n\n";

    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    testcase6();
    testcase7();
    testcase8();
    testcase9();
    testcase10();
    testcase11();
    testcase12();
    testcase13();
    testcase14();
    testcase15();

    return 0;
}

void testcase1() {
    cout << "Testcase 1 (Pointer arithmetic on 2D array): ";
    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int *p = &a[0][0];
    p = p + 4;
    cout << *p << "\n";
}

void testcase2() {
    cout << "Testcase 2 (Pointer to pointer update): ";
    int x = 10;
    int *p = &x;
    int **q = &p;
    **q = **q + 5;
    cout << x << " " << **q << "\n";
}

void testcase3() {
    cout << "Testcase 3 (Dangling pointer demo): ";
    int *p = (int*)malloc(sizeof(int));
    *p = 99;
    free(p);
    cout << "value after free: (garbage/undefined)\n";
}

void testcase4() {
    cout << "Testcase 4 (Pointer to array): ";
    int arr[5] = {10,20,30,40,50};
    int (*p)[5] = &arr;
    cout << (*p)[3] << "\n";
}

void testcase5() {
    cout << "Testcase 5 (Function pointer): ";
    auto fun = [](int x){ return x*3; };
    int (*fp)(int) = fun;
    cout << fp(7) << "\n";
}

void testcase6() {
    cout << "Testcase 6 (Void pointer casting): ";
    double d = 6.28;
    void *vp = &d;
    cout << *((double*)vp) << "\n";
}

void testcase7() {
    cout << "Testcase 7 (Pointer increment with struct): ";
    struct P { int x, y; };
    P arr[2] = {{1,2},{3,4}};
    P *p = arr;
    p++;
    cout << p->x << " " << p->y << "\n";
}

void testcase8() {
    cout << "Testcase 8 (Pointer difference): ";
    int arr[] = {5,10,15,20,25};
    int *p = arr;
    int *q = arr + 4;
    cout << q - p << "\n";
}

void testcase9() {
    cout << "Testcase 9 (Char pointer & string literal): ";
    char *s = (char*)"Hello";
    cout << *(s+1) << "\n";
}

void testcase10() {
    cout << "Testcase 10 (Null pointer check): ";
    int *p = NULL;
    cout << (p == NULL ? 1 : 0) << "\n";
}

void testcase11() {
    cout << "Testcase 11 (Dynamic 2D array): ";
    int **a = new int*[2];
    for(int i=0;i<2;i++) a[i] = new int[2]{i, i+1};
    cout << a[1][0] + a[0][1] << "\n";

    for(int i=0;i<2;i++) delete[] a[i];
    delete[] a;
}

void testcase12() {
    cout << "Testcase 12 (Pointer aliasing): ";
    int x = 5;
    int y = 7;
    int *p = &x;
    int *q = p;
    *q = 11;
    cout << x << " " << *p << " " << *q << "\n";
}

void testcase13() {
    cout << "Testcase 13 (Pointer to const & const pointer): ";
    int x = 10;
    const int *p = &x;
    int * const q = &x;
    x = 20;
    cout << *p + *q << "\n";
}

void testcase14() {
    cout << "Testcase 14 (Pointer swapping): ";
    int a = 3, b = 9;
    int *p = &a;
    int *q = &b;
    int *temp = p;
    p = q;
    q = temp;
    cout << *p << " " << *q << "\n";
}

void testcase15() {
    cout << "Testcase 15 (Double pointer dynamic allocation): ";
    int **p = new int*;
    *p = new int(50);
    cout << **p << "\n";
    delete *p;
    delete p;
}
