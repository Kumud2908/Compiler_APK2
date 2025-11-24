#include <stdio.h>

// Test switch with various cases, fallthrough, and nested structures
int main() {
    int choice = 2;
    int value = 10;
    
    // Basic switch
    switch (choice) {
        case 1:
            printf("Case 1\n");
            break;
        case 2:
            printf("Case 2\n");
            value = value * 2;
            break;
        case 3:
        case 4:
            printf("Case 3 or 4\n");
            break;
        default:
            printf("Default case\n");
    }
    
    printf("Value: %d\n", value);
    
    // Switch in loop
    int i;
    for (i = 0; i < 5; i = i + 1) {
        switch (i) {
            case 0:
                printf("Zero\n");
                break;
            case 1:
                printf("One\n");
                continue;
            case 2:
                printf("Two\n");
                break;
            default:
                printf("Other: %d\n", i);
        }
    }
    
    // Nested switch
    int outer = 1;
    int inner = 2;
    
    switch (outer) {
        case 1:
            switch (inner) {
                case 1:
                    printf("Inner 1\n");
                    break;
                case 2:
                    printf("Inner 2\n");
                    break;
            }
            break;
        default:
            printf("Outer default\n");
    }
    
    return 0;
}
