/*
 * ============================================================
 *  FIBONACCI SEQUENCE
 * ============================================================
 * THEORY:
 *   The Fibonacci sequence is defined by the recurrence:
 *       F(0) = 0
 *       F(1) = 1
 *       F(n) = F(n-1) + F(n-2)   for n >= 2
 *
 *   Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...
 *
 *   Each number is the sum of the two preceding numbers.
 *   Found throughout nature: flower petals, spiral shells,
 *   branching trees, and the golden ratio (φ ≈ 1.618...).
 *
 * THREE APPROACHES implemented below:
 *   1. Recursive         — elegant, but exponential time
 *   2. Iterative         — optimal time and space
 *   3. Dynamic Programming (Memoization) — caches results
 *
 * ─────────────────────────────────────────────────────────
 * 1. RECURSIVE
 *    Time  : O(2ⁿ)  — Each call branches into two sub-calls;
 *                      massive repeated work.
 *    Space : O(n)   — Call stack depth is n.
 *
 * 2. ITERATIVE
 *    Time  : O(n)   — Single loop, no repeated work.
 *    Space : O(1)   — Only two variables needed.
 *
 * 3. MEMOIZATION (Top-Down Dynamic Programming)
 *    Time  : O(n)   — Each sub-problem solved exactly once.
 *    Space : O(n)   — Memo array of size n+1.
 * ============================================================
 */

#include <stdio.h>
#include <string.h>   /* for memset */

#define MAX 100

/* ── 1. Recursive ─────────────────────────────────────────
 * Directly follows the mathematical definition.
 *
 * Time  : O(2ⁿ)  — exponential, avoid for large n
 * Space : O(n)   — call stack
 */
long long fib_recursive(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

/* ── 2. Iterative ─────────────────────────────────────────
 * Uses two rolling variables; most efficient approach.
 *
 * Time  : O(n)
 * Space : O(1)
 */
long long fib_iterative(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    long long prev2 = 0, prev1 = 1, current = 0;
    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2   = prev1;
        prev1   = current;
    }
    return current;
}

/* ── 3. Memoization (Top-Down DP) ─────────────────────────
 * Caches previously computed values to avoid redundant work.
 *
 * Time  : O(n)
 * Space : O(n)  — memo array + call stack
 */
long long memo[MAX];   /* memo[i] stores F(i); -1 = uncomputed */

long long fib_memo(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (memo[n] != -1)
        return memo[n];                /* Return cached value */

    memo[n] = fib_memo(n - 1) + fib_memo(n - 2);
    return memo[n];
}

/* ── Print full Fibonacci series up to n terms ────────────
 * Uses iterative method (O(n) time, O(1) space).
 */
void print_fib_series(int n) {
    long long prev2 = 0, prev1 = 1;
    printf("Series: ");
    if (n >= 1) printf("%lld ", prev2);
    if (n >= 2) printf("%lld ", prev1);
    for (int i = 3; i <= n; i++) {
        long long cur = prev1 + prev2;
        printf("%lld ", cur);
        prev2 = prev1;
        prev1 = cur;
    }
    printf("\n");
}

int main() {
    int n;   /* Find first n Fibonacci numbers */
    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("=== FIBONACCI SEQUENCE (n = %d) ===\n\n", n);

    /* 1. Recursive */
    printf("1. Recursive  [O(2^n) time | O(n) space]\n");
    printf("   F(%d) = %lld\n\n", n, fib_recursive(n));

    /* 2. Iterative */
    printf("2. Iterative  [O(n) time | O(1) space]\n");
    printf("   F(%d) = %lld\n\n", n, fib_iterative(n));

    /* 3. Memoization */
    memset(memo, -1, sizeof(memo));    /* Initialize cache */
    printf("3. Memoized   [O(n) time | O(n) space]\n");
    printf("   F(%d) = %lld\n\n", n, fib_memo(n));

    /* Full series */
    printf("First %d Fibonacci numbers:\n", n);
    print_fib_series(n);

    return 0;
}