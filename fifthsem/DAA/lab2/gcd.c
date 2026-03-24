/*
 * ============================================================
 *  OBJECTIVE:
 *   Write a program to find the Greatest Common Divisor (GCD)
 *   of two numbers entered by the user.
 * ============================================================
 *  GCD (Greatest Common Divisor)
 * ============================================================
 * THEORY:
 *   The Greatest Common Divisor (GCD) of two integers is the
 *   largest positive integer that divides both numbers without
 *   leaving a remainder. It is widely used in simplifying
 *   fractions, cryptography, and number theory problems.
 *
 *   The Euclidean Algorithm is the most efficient method:
 *       GCD(a, b) = GCD(b, a % b)
 *       GCD(a, 0) = a   (base case)
 *
 *   Example: GCD(48, 18)
 *     GCD(48, 18) → GCD(18, 12) → GCD(12, 6) → GCD(6, 0) = 6
 *
 *   It repeatedly replaces the larger number with the
 *   remainder of dividing the two, until the remainder is 0.
 *   The last non-zero remainder is the GCD.
 *
 * TIME COMPLEXITY:
 *   O(log(min(a, b)))  — Euclidean Algorithm
 *
 * SPACE COMPLEXITY:
 *   O(1)  — Iterative version uses no extra space
 * ============================================================
 */

#include <stdio.h>

/* Function: gcd
 * Returns the GCD of two positive integers a and b
 * using the Euclidean Algorithm (iterative).
 *
 * Time  : O(log(min(a, b)))
 * Space : O(1)
 */
int gcd(int a, int b) {
    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int main() {
    int a, b;

    printf("========================================\n");
    printf("            GCD PROGRAM                 \n");
    printf("========================================\n\n");

    printf("Enter first number  : ");
    scanf("%d", &a);

    printf("Enter second number : ");
    scanf("%d", &b);

    if (a <= 0 || b <= 0) {
        printf("Invalid! Please enter positive integers.\n");
        return 1;
    }

    printf("\nFirst Number  : %d\n", a);
    printf("Second Number : %d\n", b);
    printf("GCD Result    : %d\n", gcd(a, b));

    printf("\n========================================\n");

    return 0;
}