/*
 * ============================================================
 *  OBJECTIVE:
 *   Write a program to solve the 0/1 Knapsack problem using
 *   Dynamic Programming to find the maximum value that can
 *   be carried within a given weight capacity.
 * ============================================================
 *  DYNAMIC PROGRAMMING — 0/1 KNAPSACK PROBLEM
 * ============================================================
 * THEORY:
 *   The 0/1 Knapsack problem asks: given n items each with a
 *   weight and value, and a knapsack with a maximum weight
 *   capacity W, which items should be selected to maximize
 *   the total value without exceeding the weight limit?
 *
 *   Each item can either be included (1) or excluded (0) —
 *   it cannot be broken into fractions (unlike Fractional
 *   Knapsack), making greedy approaches suboptimal here.
 *
 *   Dynamic Programming builds a 2D table dp[i][w] where
 *   each cell stores the maximum value achievable using the
 *   first i items with weight capacity w. The answer is
 *   found by filling the table bottom-up, then backtracking
 *   through the table to identify which items were selected.
 *
 *   Recurrence:
 *     dp[i][w] = dp[i-1][w]                          if weight[i] > w
 *     dp[i][w] = max(dp[i-1][w],
 *                    dp[i-1][w-weight[i]] + value[i]) if weight[i] <= w
 *
 * TIME COMPLEXITY:
 *   O(n × W)  — Fill every cell of the n × W DP table
 *               where n = number of items, W = capacity
 *
 * SPACE COMPLEXITY:
 *   O(n × W)  — DP table of size (n+1) × (W+1)
 * ============================================================
 */

#include <stdio.h>

#define MAX_ITEMS    20
#define MAX_CAPACITY 100

int dp[MAX_ITEMS + 1][MAX_CAPACITY + 1];   /* DP table */

/* Helper: return maximum of two integers */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Function: knapsack
 * Fills dp table and returns the maximum value achievable.
 *
 * Time  : O(n * W)
 * Space : O(n * W)
 */
int knapsack(int weight[], int value[], int n, int W) {
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;   /* Base case: no items or zero capacity */
            } else if (weight[i-1] <= w) {
                /* Max of: excluding item i, or including item i */
                dp[i][w] = max(dp[i-1][w],
                               dp[i-1][w - weight[i-1]] + value[i-1]);
            } else {
                dp[i][w] = dp[i-1][w];   /* Item too heavy, skip */
            }
        }
    }
    return dp[n][W];
}

/* Function: print_selected_items
 * Backtracks through dp table to find which items were selected.
 *
 * Time  : O(n)
 */
void print_selected_items(int weight[], int value[], int n, int W) {
    int w = W;
    printf("\nSelected Items:\n");
    printf("  %-8s %-10s %-10s\n", "Item", "Weight", "Value");
    printf("  %-8s %-10s %-10s\n", "----", "------", "-----");

    int total_w = 0, total_v = 0;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {   /* Item i was included */
            printf("  %-8d %-10d %-10d\n", i, weight[i-1], value[i-1]);
            total_w += weight[i-1];
            total_v += value[i-1];
            w -= weight[i-1];
        }
    }
    printf("  %-8s %-10s %-10s\n", "--------", "----------", "----------");
    printf("  %-8s %-10d %-10d\n", "Total", total_w, total_v);
}

int main() {
    int n, W;
    int weight[MAX_ITEMS], value[MAX_ITEMS];

    printf("========================================\n");
    printf("     0/1 KNAPSACK — DYNAMIC PROGRAMMING \n");
    printf("========================================\n\n");

    printf("Enter number of items   : ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_ITEMS) {
        printf("Invalid! Enter between 1 and %d.\n", MAX_ITEMS);
        return 1;
    }

    printf("Enter knapsack capacity : ");
    scanf("%d", &W);

    if (W <= 0 || W > MAX_CAPACITY) {
        printf("Invalid! Enter capacity between 1 and %d.\n", MAX_CAPACITY);
        return 1;
    }

    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d — Enter weight and value: ", i + 1);
        scanf("%d %d", &weight[i], &value[i]);
    }

    /* Display input summary */
    printf("\nItems Summary:\n");
    printf("  %-8s %-10s %-10s\n", "Item", "Weight", "Value");
    printf("  %-8s %-10s %-10s\n", "----", "------", "-----");
    for (int i = 0; i < n; i++)
        printf("  %-8d %-10d %-10d\n", i + 1, weight[i], value[i]);

    printf("\nKnapsack Capacity : %d\n", W);

    int max_value = knapsack(weight, value, n, W);

    printf("Maximum Value     : %d\n", max_value);

    print_selected_items(weight, value, n, W);

    printf("\n========================================\n");

    return 0;
}