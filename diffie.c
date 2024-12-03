#include <stdio.h>
#include <math.h>

// Function to perform modular exponentiation
// It returns (base^exp) % mod
long long modularExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {  // If exp is odd
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long p, g, a, b, A, B, secretA, secretB;

    // Step 1: Input public prime number p and base g
    printf("Enter a prime number p: ");
    scanf("%lld", &p);
    printf("Enter a base g: ");
    scanf("%lld", &g);

    // Step 2: Generate private keys a and b for Party A and Party B
    printf("Enter private key for Party A: ");
    scanf("%lld", &a);
    printf("Enter private key for Party B: ");
    scanf("%lld", &b);

    // Step 3: Compute A = g^a % p and B = g^b % p
    A = modularExponentiation(g, a, p);
    B = modularExponentiation(g, b, p);

    printf("Party A sends: %lld\n", A);
    printf("Party B sends: %lld\n", B);

    // Step 4: Compute the shared secret key for both parties
    secretA = modularExponentiation(B, a, p);  // Party A's secret key
    secretB = modularExponentiation(A, b, p);  // Party B's secret key

    // Step 5: Verify that both parties have the same shared secret
    printf("Party A's computed shared secret: %lld\n", secretA);
    printf("Party B's computed shared secret: %lld\n", secretB);

    if (secretA == secretB) {
        printf("The shared secret is successfully established.\n");
    } else {
        printf("Error: Shared secrets do not match.\n");
    }

    return 0;
}

