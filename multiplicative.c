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

// Function to compute the modular multiplicative inverse
int multiplicativeInverse(int a, int m) {
    int x, y;
    int gcd = extendedGCD(a, m, &x, &y);

    // Multiplicative inverse exists only if GCD is 1
    if (gcd != 1) {
        printf("Multiplicative inverse does not exist (GCD is %d).\n", gcd);
        return -1;
    }

    // Ensure the result is positive
    int inverse = (x % m + m) % m;
    return inverse;
}

int main() {
    int a, m;

    printf("Enter the number (a): ");
    scanf("%d", &a);

    printf("Enter the modulus (m): ");
    scanf("%d", &m);

    int result = multiplicativeInverse(a, m);
    if (result != -1) {
        printf("The multiplicative inverse of %d modulo %d is: %d\n", a, m, result);
    }

    return 0;
}

