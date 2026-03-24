/*
 * ============================================================
 *  BINARY SEARCH
 * ============================================================
 * THEORY:
 *   Binary Search works on a SORTED array. It repeatedly
 *   divides the search interval in half:
 *   - Compare the target with the middle element.
 *   - If target == middle  → found, return index.
 *   - If target  < middle  → search the LEFT half.
 *   - If target  > middle  → search the RIGHT half.
 *   - If interval is empty → element not present.
 *
 *   Works like looking up a word in a dictionary:
 *   open to the middle, decide which half to look in,
 *   repeat — drastically cutting down the search space.
 *
 * PREREQUISITE: Array must be sorted.
 *
 * TIME COMPLEXITY:
 *   Best Case    : O(1)       — Target is the middle element
 *   Average Case : O(log n)
 *   Worst Case   : O(log n)
 *
 * SPACE COMPLEXITY:
 *   Iterative : O(1)
 *   Recursive : O(log n)  — due to call stack
 * ============================================================
 */

#include <stdio.h>

/* ── Iterative Binary Search ──────────────────────────────
 * Returns index of 'target' in sorted array 'arr[0..n-1]',
 * or -1 if not found.
 *
 * Time  : O(log n)
 * Space : O(1)
 */
int binary_search_iterative(int arr[], int n, int target) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;   /* Avoids integer overflow */

        if (arr[mid] == target)
            return mid;                      /* Found */
        else if (arr[mid] < target)
            low = mid + 1;                   /* Search right half */
        else
            high = mid - 1;                  /* Search left half */
    }
    return -1;                               /* Not found */
}

/* ── Recursive Binary Search ──────────────────────────────
 * Returns index of 'target' in sorted arr[low..high],
 * or -1 if not found.
 *
 * Time  : O(log n)
 * Space : O(log n)  — recursive call stack
 */
int binary_search_recursive(int arr[], int low, int high, int target) {
    if (low > high)
        return -1;                           /* Base case: not found */

    int mid = low + (high - low) / 2;

    if (arr[mid] == target)
        return mid;
    else if (arr[mid] < target)
        return binary_search_recursive(arr, mid + 1, high, target);
    else
        return binary_search_recursive(arr, low, mid - 1, target);
}

int main() {
    int arr[100];
    int n, target;

    printf("=== BINARY SEARCH ===\n");

    /* Take size input */
    printf("Enter number of elements: ");
    scanf("%d", &n);

    /* Take sorted array input */
    printf("Enter %d elements (sorted): ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    /* Take target input */
    printf("Enter element to search: ");
    scanf("%d", &target);

    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\nTarget: %d\n\n", target);

    /* Iterative */
    int idx = binary_search_iterative(arr, n, target);
    if (idx != -1)
        printf("[Iterative] Found %d at index %d\n", target, idx);
    else
        printf("[Iterative] %d not found\n", target);

    /* Recursive */
    idx = binary_search_recursive(arr, 0, n - 1, target);
    if (idx != -1)
        printf("[Recursive] Found %d at index %d\n", target, idx);
    else
        printf("[Recursive] %d not found\n", target);

    return 0;
}