/*
 * ============================================================
 *  OBJECTIVE:
 *   Write a program to find the minimum number of scalar
 *   multiplications needed to multiply a chain of matrices
 *   using the Matrix Chain Multiplication algorithm.
 * ============================================================
 *  MATRIX CHAIN MULTIPLICATION
 * ============================================================
 * THEORY:
 *   Matrix Chain Multiplication determines the most efficient
 *   way to parenthesize a sequence of matrices so that the
 *   total number of scalar multiplications is minimized.
 *   It does NOT actually multiply the matrices — it only finds
 *   the optimal order/parenthesization to do so.
 *
 *   Multiplying matrix A(p×q) with B(q×r) costs p*q*r scalar
 *   multiplications. The order of parenthesization dramatically
 *   affects the total cost even though the result is the same.
 *
 *   Dynamic Programming is used to solve this by breaking the
 *   problem into overlapping subproblems: for each sub-chain
 *   of matrices, find the split point k that minimizes cost,
 *   storing results in a 2D table to avoid recomputation.
 *
 *   The input is an array of dimensions p[] where matrix i
 *   has dimensions p[i-1] x p[i], for i = 1 to n.
 *
 * TIME COMPLEXITY:
 *   O(n³)  — Three nested loops over the chain length
 *
 * SPACE COMPLEXITY:
 *   O(n²)  — DP table dp[n][n] and split table s[n][n]
 * ============================================================
 */

#include <stdio.h>
#include <limits.h>

#define MAX 20

int dp[MAX][MAX];   /* dp[i][j] = min cost to multiply matrices i..j */
int s[MAX][MAX];    /* s[i][j]  = optimal split point for i..j        */

/* Function: matrix_chain_order
 * Fills dp[][] with minimum multiplication costs and
 * s[][] with the optimal split points.
 *
 * p[] : dimensions array of size n+1
 * n   : number of matrices
 *
 * Time  : O(n³)
 * Space : O(n²)
 */
void matrix_chain_order(int p[], int n) {
    /* Single matrix — zero cost */
    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;

    /* l = chain length (number of matrices in sub-chain) */
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;

            /* Try every possible split point k */
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + p[i-1] * p[k] * p[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    s[i][j]  = k;    /* Record optimal split */
                }
            }
        }
    }
}

/* Function: print_optimal_parens
 * Recursively prints the optimal parenthesization.
 */
void print_optimal_parens(int i, int j) {
    if (i == j) {
        printf("M%d", i);
    } else {
        printf("(");
        print_optimal_parens(i, s[i][j]);
        printf(" x ");
        print_optimal_parens(s[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int n;

    printf("========================================\n");
    printf("   MATRIX CHAIN MULTIPLICATION          \n");
    printf("========================================\n\n");

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX) {
        printf("Invalid! Enter between 1 and %d.\n", MAX - 1);
        return 1;
    }

    int p[MAX];
    printf("Enter %d dimensions (d0 d1 ... d%d)\n", n + 1, n);
    printf("(Matrix i has dimensions p[i-1] x p[i])\n");
    printf("Enter dimensions: ");
    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    /* Display matrices and their dimensions */
    printf("\nMatrices:\n");
    for (int i = 1; i <= n; i++)
        printf("  M%d : %d x %d\n", i, p[i-1], p[i]);

    matrix_chain_order(p, n);

    printf("\nMinimum Multiplications : %d\n", dp[1][n]);
    printf("Optimal Parenthesization: ");
    print_optimal_parens(1, n);
    printf("\n");

    printf("\n========================================\n");

    return 0;
}