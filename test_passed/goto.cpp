#include <stdio.h>

int main() {
    int i = 0, j = 0;
    
outer_loop:
    if (i >= 3)
        goto done;
    
    j = 0;
    
inner_loop:
    if (j >= 3)
        goto next_i;
    
    if (i == 1 && j == 1) {
        printf("Skipping [%d][%d]\n", i, j);
        j++;
        goto inner_loop;
    }
    
    printf("[%d][%d]\n", i, j);
    j++;
    goto inner_loop;
    
next_i:
    i++;
    goto outer_loop;
    
done:
    printf("Complete!\n");
    return 0;
}