#include <stdio.h>

// Function to compute GCD and coefficients x and y
int extendedGCD(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1; // Coefficients for the recursive step
    int gcd = extendedGCD(b, a % b, &x1, &y1);

    // Update x and y using results from recursive step
    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd;
}

int main() {
    int a, b, x, y, gcd;

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    // Compute GCD and coefficients
    gcd = extendedGCD(a, b, &x, &y);

    printf("GCD of %d and %d is: %d\n", a, b, gcd);
    printf("Coefficients x and y are: %d and %d\n", x, y);

    return 0;
}

