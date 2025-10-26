// #include <iostream>


// int fib(int n) {
//     if (n <= 1) return n;
//     return fib(n - 1) + fib(n - 2);
// }

// int main() {
//     printf("%d",fib(6));
//     return 0;
// }

#include <iostream>


int main() {
    printf("%d",factorial(5)); // factorial not declared yet
    return 0;
}

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

//infinite recursion
// #include <iostream>


// void infiniteRec() {
   
//     infiniteRec();
// }

// int main() {
//     infiniteRec();
//     return 0;
// }


