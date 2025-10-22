#include <stdio.h>

int main() {
    // int x = 5;
    
    // // Test 1: If-else statements
    // if (x > 0) {
    //     printf("Positive\n");
    // } else {
    //     printf("Non-positive\n");
    // }
    
    // // Test 2: While loop
    // int i = 0;
    // while (i < 10) {
    //     i++;
    // }
    
    // // Test 3: Do-while loop
    // do {
    //     x--;
    // } while (x > 0);
    
    // // Test 4: For loop
    // for (int j = 0; j < 5; j++) {
    //     printf("%d\n", j);
    // }
    
    // // Test 5: Break outside loop
    // //break;  // ERROR: break outside loop
    
    // // Test 6: Continue outside loop
    // //continue;  // ERROR: continue outside loop
    
    // // Test 7: Valid break in loop
    // while (1) {
    //     if (x == 0) break;  // OK
    //     x--;
    // }
    int x=4;
    int j=0;
    for(int k=0;k<10;k++){
    while(j<5){
        switch(x){
            case 1:
                break; // should break switch, not outer loops
            default:
                continue; // should continue while loop
        }
    }
}

    
    return 0;
}