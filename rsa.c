#include <stdio.h>
#include <math.h>

// Function to compute GCD using the Euclidean method
int gcd(int a, int b) {
    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

// Function to compute (base^exp) % mod using modular exponentiation
int modularExponentiation(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) { // If exp is odd
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }

    return result;
}

// Function to compute the modular inverse of e modulo phi
int modularInverse(int e, int phi) {
    int x, y;
    int gcd, temp_phi = phi;

    // Extended Euclidean Algorithm
    int u1 = 1, u2 = 0, u3 = e;
    int v1 = 0, v2 = 1, v3 = phi;
    while (v3 != 0) {
        int q = u3 / v3;
        int t1 = u1 - q * v1;
        int t2 = u2 - q * v2;
        int t3 = u3 - q * v3;

        u1 = v1; u2 = v2; u3 = v3;
        v1 = t1; v2 = t2; v3 = t3;
    }

    // Ensure positive result
    return (u1 + temp_phi) % temp_phi;
}

int main() {
    int p, q, n, phi, e, d, message, encrypted, decrypted;

    // Step 1: Input two prime numbers
    printf("Enter two prime numbers (p and q): ");
    scanf("%d %d", &p, &q);

    // Step 2: Compute n and phi
    n = p * q;
    phi = (p - 1) * (q - 1);

    // Step 3: Choose e such that 1 < e < phi and GCD(e, phi) = 1
    printf("Enter a value for e (1 < e < %d): ", phi);
    scanf("%d", &e);
    while (gcd(e, phi) != 1) {
        printf("e must be coprime with %d. Enter again: ", phi);
        scanf("%d", &e);
    }

    // Step 4: Compute the decryption key d
    d = modularInverse(e, phi);

    printf("Public Key: (n = %d, e = %d)\n", n, e);
    printf("Private Key: (n = %d, d = %d)\n", n, d);

    // Step 5: Encrypt a message
    printf("Enter the message to encrypt (integer < %d): ", n);
    scanf("%d", &message);
    encrypted = modularExponentiation(message, e, n);
    printf("Encrypted message: %d\n", encrypted);

    // Step 6: Decrypt the message
    decrypted = modularExponentiation(encrypted, d, n);
    printf("Decrypted message: %d\n", decrypted);

    return 0;
}

