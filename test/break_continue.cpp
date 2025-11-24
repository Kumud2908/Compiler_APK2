#include <stdio.h>

int main() {
    int i;
    
    // Test 1: break in for loop
    printf("Test 1: break in for loop\n");
    for (i = 0; i < 10; i = i + 1) {
        if (i == 5) {
            break;
        }
        printf("%d ", i);
    }
    printf("\n");
    
    // Test 2: continue in for loop
    printf("\nTest 2: continue in for loop\n");
    for (i = 0; i < 10; i = i + 1) {
        if (i == 3 || i == 7) {
            continue;
        }
        printf("%d ", i);
    }
    printf("\n");
    
    // Test 3: break in while loop
    printf("\nTest 3: break in while loop\n");
    i = 0;
    while (i < 10) {
        if (i == 6) {
            break;
        }
        printf("%d ", i);
        i = i + 1;
    }
    printf("\n");
    
    // Test 4: continue in while loop
    printf("\nTest 4: continue in while loop\n");
    i = 0;
    while (i < 10) {
        i = i + 1;
        if (i == 4 || i == 8) {
            continue;
        }
        printf("%d ", i);
    }
    printf("\n");
    
    // Test 5: break in do-while
    printf("\nTest 5: break in do-while\n");
    i = 0;
    do {
        if (i == 4) {
            break;
        }
        printf("%d ", i);
        i = i + 1;
    } while (i < 10);
    printf("\n");
    
    // Test 6: continue in do-while
    printf("\nTest 6: continue in do-while\n");
    i = 0;
    do {
        i = i + 1;
        if (i == 2 || i == 6) {
            continue;
        }
        printf("%d ", i);
    } while (i < 8);
    printf("\n");
    
    // Test 7: nested loops with break
    printf("\nTest 7: nested loops with break\n");
    int j;
    for (i = 0; i < 3; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (j == 3) {
                break;
            }
            printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }
    
    // Test 8: nested loops with continue
    printf("\nTest 8: nested loops with continue\n");
    for (i = 0; i < 3; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (j == 2) {
                continue;
            }
            printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }
    
    // Test 9: combined break and continue
    printf("\nTest 9: combined break and continue\n");
    for (i = 0; i < 20; i = i + 1) {
        if (i < 5) {
            continue;
        }
        if (i > 12) {
            break;
        }
        if (i == 8 || i == 10) {
            continue;
        }
        printf("%d ", i);
    }
    printf("\n");
    
    return 0;
}
