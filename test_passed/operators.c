#include <stdio.h>

int main() {
    printf("=== Arithmetic Operators ===\n");
    int a = 10, b = 3;
    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d\n", a / b);
    printf("a %% b = %d\n", a % b);
    
    printf("\n=== Comparison Operators ===\n");
    printf("a == b: %d\n", a == b);
    printf("a != b: %d\n", a != b);
    printf("a < b: %d\n", a < b);
    printf("a > b: %d\n", a > b);
    printf("a <= b: %d\n", a <= b);
    printf("a >= b: %d\n", a >= b);
    
    printf("\n=== Logical Operators ===\n");
    int x = 1, y = 0;
    printf("x = %d, y = %d\n", x, y);
    printf("x && y: %d\n", x && y);
    printf("x || y: %d\n", x || y);
    printf("!x: %d\n", !x);
    printf("!y: %d\n", !y);
    
    printf("\n=== Bitwise Operators ===\n");
    int p = 5, q = 3;
    printf("p = %d, q = %d\n", p, q);
    printf("p & q = %d\n", p & q);
    printf("p | q = %d\n", p | q);
    printf("p ^ q = %d\n", p ^ q);
    printf("~p = %d\n", ~p);
    printf("p << 1 = %d\n", p << 1);
    printf("p >> 1 = %d\n", p >> 1);
    
    printf("\n=== Increment/Decrement Operators ===\n");
    int m = 5;
    printf("m = %d\n", m);
    printf("m++ = %d\n", m++);
    printf("m = %d\n", m);
    printf("++m = %d\n", ++m);
    printf("m-- = %d\n", m--);
    printf("m = %d\n", m);
    printf("--m = %d\n", --m);
    
    printf("\n=== Assignment Operators ===\n");
    int n = 10;
    printf("n = %d\n", n);
    n += 5;
    printf("n += 5: %d\n", n);
    n -= 3;
    printf("n -= 3: %d\n", n);
    n *= 2;
    printf("n *= 2: %d\n", n);
    n /= 4;
    printf("n /= 4: %d\n", n);
    n %= 3;
    printf("n %%= 3: %d\n", n);
  
    printf("\n=== Loop Tests ===\n");
    /* for loop */
    // for (int i=0; i<3; i++)
    //     printf("for i=%d\n", i);

    /* while loop */
    int j = 0;
    while (j < 3) {
        printf("while j=%d\n", j);
        j++;
    }
    
    // for(int i=0;i<4;i++) printf("h");
    
    printf("\n=== Complex Expressions ===\n");
    int r = 5, s = 3, t = 2;
    printf("r = %d, s = %d, t = %d\n", r, s, t);
    printf("r + s * t = %d\n", r + s * t);
    printf("(r + s) * t = %d\n", (r + s) * t);
    printf("r * s + t * 2 - 1 = %d\n", r * s + t * 2 - 1);
    printf("r / s + t * s - r %% s = %d\n", r / s + t * s - r % s);
    
    printf("\n=== Nested Operations ===\n");
    int nested = ((10 + 5) * 2 - 3) / 4;
    printf("((10 + 5) * 2 - 3) / 4 = %d\n", nested);
    
    printf("\n=== Combined Logical & Comparison ===\n");
    int val1 = 10, val2 = 20, val3 = 15;
    printf("val1 = %d, val2 = %d, val3 = %d\n", val1, val2, val3);
    printf("(val1 < val2) && (val3 > val1): %d\n", (val1 < val2) && (val3 > val1));
    printf("(val1 > val2) || (val3 < val2): %d\n", (val1 > val2) || (val3 < val2));
    printf("!(val1 == val2) && (val3 != val1): %d\n", !(val1 == val2) && (val3 != val1));
    
    printf("\n=== Bitwise Complex Operations ===\n");
    int bit1 = 12, bit2 = 10;
    printf("bit1 = %d, bit2 = %d\n", bit1, bit2);
    printf("(bit1 & bit2) | (bit1 ^ bit2) = %d\n", (bit1 & bit2) | (bit1 ^ bit2));
    printf("(bit1 << 2) >> 1 = %d\n", (bit1 << 2) >> 1);
    printf("~(bit1 & bit2) = %d\n", ~(bit1 & bit2));
    
    printf("\n=== Mixed Increment/Decrement ===\n");
    int mix = 10;
    printf("mix = %d\n", mix);
    printf("mix++ + ++mix = %d\n", mix++ + ++mix);
    printf("mix = %d\n", mix);
    
    printf("\n=== Chained Assignments ===\n");
    int c1, c2, c3;
    c1 = c2 = c3 = 5;
    printf("c1 = c2 = c3 = 5: c1=%d, c2=%d, c3=%d\n", c1, c2, c3);
    c1 += c2 += c3;
    printf("c1 += c2 += c3: c1=%d, c2=%d, c3=%d\n", c1, c2, c3);
    
    printf("\n=== Ternary-like with Logical ===\n");
    int check = 15;
    int result = (check > 10) && (check < 20);
    printf("check = %d, (check > 10) && (check < 20) = %d\n", check, result);
    
    printf("\n=== Division by Powers of 2 ===\n");
    int div_test = 32;
    printf("div_test = %d\n", div_test);
    printf("div_test / 2 = %d\n", div_test / 2);
    printf("div_test >> 1 = %d\n", div_test >> 1);
    printf("div_test / 4 = %d\n", div_test / 4);
    printf("div_test >> 2 = %d\n", div_test >> 2);
    
    printf("\n=== Modulo with Negative ===\n");
    int mod1 = 17, mod2 = 5;
    printf("mod1 = %d, mod2 = %d\n", mod1, mod2);
    printf("mod1 %% mod2 = %d\n", mod1 % mod2);
    printf("mod1 %% -mod2 = %d\n", mod1 % -mod2);
    
    printf("\n=== Operator Precedence Test ===\n");
    int prec = 2 + 3 * 4 - 10 / 2;
    printf("2 + 3 * 4 - 10 / 2 = %d\n", prec);
    int prec2 = 10 < 20 && 5 > 3 || 0;
    printf("10 < 20 && 5 > 3 || 0 = %d\n", prec2);
    
    return 0;
}