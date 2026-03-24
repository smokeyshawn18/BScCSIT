#include <stdio.h>

// Function to compute (base^exp) % mod
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Function to compute gcd
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular inverse (d)
long long mod_inverse(long long e, long long phi) {
    for (long long d = 1; d < phi; d++) {
        if ((d * e) % phi == 1)
            return d;
    }
    return -1;
}

int main() {
    long long p, q, n, phi;
    long long e, d;
    long long message, encrypted, decrypted;

    printf("Enter first prime number (p): ");
    scanf("%lld", &p);

    printf("Enter second prime number (q): ");
    scanf("%lld", &q);

    // Step 1: Compute n and phi
    n = p * q;
    phi = (p - 1) * (q - 1);

    // Step 2: Choose e
    printf("Enter public key exponent (e): ");
    scanf("%lld", &e);

    // Ensure gcd(e, phi) = 1
    if (gcd(e, phi) != 1) {
        printf("Invalid e. It must be coprime with φ(n).\n");
        return 1;
    }

    // Step 3: Compute d
    d = mod_inverse(e, phi);

    if (d == -1) {
        printf("Modular inverse not found.\n");
        return 1;
    }

    printf("\nPublic Key: (e = %lld, n = %lld)\n", e, n);
    printf("Private Key: (d = %lld, n = %lld)\n", d, n);

    // Input message
    printf("\nEnter numeric message (M < n): ");
    scanf("%lld", &message);

    // Encryption
    encrypted = mod_pow(message, e, n);
    printf("Encrypted message: %lld\n", encrypted);

    // Decryption
    decrypted = mod_pow(encrypted, d, n);
    printf("Decrypted message: %lld\n", decrypted);

    return 0;
}