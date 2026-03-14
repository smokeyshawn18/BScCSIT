/*
 * Diffie-Hellman Key Exchange Implementation in C

 * Description:
 * This program demonstrates the Diffie-Hellman key exchange algorithm.
 * It simulates two parties (Alice and Bob) who agree on a shared secret key
 * over an insecure channel without ever transmitting the key itself.
 *
 * Public parameters:
 *   - p : large prime number (modulus)
 *   - g : primitive root modulo p (generator)
 *
 * Steps:
 *   1. Alice chooses private key 'a' → computes public key A = g^a mod p
 *   2. Bob chooses private key 'b' → computes public key B = g^b mod p
 *   3. They exchange A and B publicly
 *   4. Alice computes K = B^a mod p
 *   5. Bob computes K = A^b mod p
 *   6. Both get the same shared secret K
 *
 * NOTE: For lab demonstration, use small values (p < 10^9).
 *       In real life, we use very large primes (2048+ bits) with libraries like OpenSSL.
 *       This uses efficient square-and-multiply modular exponentiation.
 */

#include <stdio.h>
#include <stdlib.h>

// Function for modular exponentiation: (base^exp) mod mod
// Uses binary exponentiation (O(log exp) time) to avoid overflow issues
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;                // Reduce base first
    while (exp > 0) {
        if (exp % 2 == 1) {           // If exponent is odd
            result = (result * base) % mod;
        }
        base = (base * base) % mod;   // Square the base
        exp /= 2;                     // Halve the exponent
    }
    return result;
}

int main() {
    long long p, g;                   // Public parameters
    long long a, b;                   // Private keys
    long long A, B;                   // Public keys
    long long K_alice, K_bob;         // Shared secret keys

    printf("=== Diffie-Hellman Key Exchange Demo (BSc CSIT Cryptography Lab) ===\n\n");

    // Input public parameters (common example: p=23, g=5)
    printf("Enter a prime number p: ");
    scanf("%lld", &p);
    printf("Enter primitive root g (mod p): ");
    scanf("%lld", &g);

    // Alice's side
    printf("\nAlice: Enter your private key 'a' (1 < a < p-1): ");
    scanf("%lld", &a);
    A = mod_pow(g, a, p);
    printf("Alice computes public key A = g^a mod p = %lld\n", A);

    // Bob's side
    printf("Bob: Enter your private key 'b' (1 < b < p-1): ");
    scanf("%lld", &b);
    B = mod_pow(g, b, p);
    printf("Bob computes public key B = g^b mod p = %lld\n", B);

    // Key exchange simulation
    printf("\n--- Alice and Bob exchange public keys A and B over insecure channel ---\n");

    // Alice computes shared key
    K_alice = mod_pow(B, a, p);
    printf("Alice computes shared secret K = B^a mod p = %lld\n", K_alice);

    // Bob computes shared key
    K_bob = mod_pow(A, b, p);
    printf("Bob computes shared secret K = A^b mod p = %lld\n", K_bob);

    // Verification
    if (K_alice == K_bob) {
        printf("\nSUCCESS: Shared secret keys match! K = %lld\n", K_alice);
        printf("They can now use this key for symmetric encryption (e.g., AES).\n");
    } else {
        printf("\nERROR: Keys do not match (bug in implementation).\n");
    }

    printf("\n=== Lab Report Usage Tips ===\n");
    printf("1. Compile: gcc diffie_hellman.c -o dh\n");
    printf("2. Run: ./dh\n");
    printf("3. Test with standard values:\n");
    printf("   p = 23, g = 5, a = 6, b = 15 → K = 2\n");
    printf("   p = 17, g = 3, a = 5, b = 7 → K = 6\n");
    printf("4. For report: Include this code, output screenshot, and explain each step.\n");

    return 0;
}