// Simplified function pointer test
int add(int x, int y) {
    return x + y;
}

int main() {
    int (*func_ptr)(int, int);
    func_ptr = add;
    
    int result = func_ptr(5, 3);
    printf("Result: %d\n", result);
    
    return 0;
}
