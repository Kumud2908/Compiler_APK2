// Test Case 4: Arrays, pointers, function calls, and basic arithmetic operations.
int sum(int arr[], int n) {
    int s = 0;
    for (int i = 0; i < n; i++) s = s + arr[i];
    return s;
}

int main() {
    int a[3] = {1,2,3};
    int *p = a;
    int result = sum(a, 3);
    printf("%d", result);
    return 0;
}