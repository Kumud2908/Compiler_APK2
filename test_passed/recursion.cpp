// Complex recursive functions
#include <stdio.h>

// Fibonacci with recursion
int fib(int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

// Factorial with recursion
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// GCD using Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    printf("Fib(7): %d\n", fib(7));           // 13
    printf("Factorial(5): %d\n", factorial(5)); // 120
    printf("GCD(48, 18): %d\n", gcd(48, 18)); // 6
    return 0;
}
