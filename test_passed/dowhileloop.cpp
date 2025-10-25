
    #include <stdio.h>

int main() {
    int i = 0, j = 0, sum = 0;
    int limit = 5;

    do {
        j = 0;
        do {
            sum += i * j;        // accumulate product
            if ((i + j) % 2 == 0) {
                sum += 1;        // add 1 if sum of indices is even
            } else {
                sum -= 1;        // subtract 1 otherwise
            }
            j++;
        } while (j < limit - i); // inner loop depends on outer loop variable

        if (sum % 10 == 0) {
            i += 2;              // skip a value of i when sum divisible by 10
        } else {
            i++;
        }

        printf("i=%d, sum=%d\n", i, sum);

    } while (i < limit);

    return 0;
}

