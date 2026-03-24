/*
 * ============================================================
 *  SELECTION SORT
 * ============================================================
 * THEORY:
 *   Selection Sort divides the array into two parts:
 *     - Sorted   (left side, built up one element at a time)
 *     - Unsorted (right side, shrinks each pass)
 *
 *   Each pass scans the unsorted part, finds the MINIMUM
 *   element, and swaps it to the front of the unsorted part
 *   (i.e., appends it to the sorted part).
 *
 *   Works like sorting books by height on a shelf:
 *   scan all books, pull out the shortest, place it first,
 *   then repeat for the remaining books.
 *
 * KEY PROPERTY:
 *   Makes at most (n-1) swaps — useful when write operations
 *   are expensive (e.g., flash memory).
 *
 * TIME COMPLEXITY:
 *   Best Case    : O(n²)   — Always scans the full unsorted part
 *   Average Case : O(n²)
 *   Worst Case   : O(n²)
 *
 * SPACE COMPLEXITY:
 *   O(1)  — In-place, no extra array needed
 *
 * STABLE SORT: NO  (swapping can change relative order)
 * ============================================================
 */

#include <stdio.h>

/* Helper: swap two integers */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Function: selection_sort
 * Sorts array 'arr' of size 'n' in ascending order.
 *
 * Time  : O(n²) — two nested loops regardless of input
 * Space : O(1)
 */
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        /* Find index of minimum element in arr[i..n-1] */
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        /* Swap minimum element with first element of unsorted part */
        if (min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}

/* Helper: print array */
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=== SELECTION SORT ===\n");
    printf("Before: ");
    print_array(arr, n);

    /* Show each pass */
    printf("\nStep-by-step:\n");
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx]) min_idx = j;

        if (min_idx != i) swap(&arr[min_idx], &arr[i]);

        printf("Pass %d : ", i + 1);
        print_array(arr, n);
    }

    printf("\nAfter : ");
    print_array(arr, n);

    return 0;
}