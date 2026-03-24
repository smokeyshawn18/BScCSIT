/*
 * ============================================================
 *  OBJECTIVE:
 *   Write a program to sort an array of integers entered by
 *   the user using the Quick Sort algorithm.
 * ============================================================
 *  QUICK SORT
 * ============================================================
 * THEORY:
 *   Quick Sort is a Divide and Conquer algorithm that selects
 *   a "pivot" element and partitions the array into two halves:
 *   elements smaller than the pivot on the left, and elements
 *   greater than the pivot on the right, then recursively sorts
 *   each half.
 *
 *   The partition step rearranges elements in-place around the
 *   pivot so that after partitioning, the pivot is in its final
 *   sorted position — no further movement needed for the pivot.
 *
 *   It is one of the fastest sorting algorithms in practice,
 *   often outperforming Merge Sort due to better cache locality
 *   and no need for extra memory during sorting.
 *
 *   Works like picking a reference card from a deck, moving
 *   all smaller cards to its left and larger cards to its right,
 *   then repeating the process for each side independently.
 *
 * TIME COMPLEXITY:
 *   Best Case    : O(n log n) — Pivot always splits array evenly
 *   Average Case : O(n log n)
 *   Worst Case   : O(n²)     — Pivot is always smallest/largest
 *                              (e.g., already sorted array)
 *
 * SPACE COMPLEXITY:
 *   O(log n)  — Recursive call stack (average)
 *   O(n)      — Worst case call stack (skewed partitions)
 *
 * STABLE SORT: NO
 * ============================================================
 */

#include <stdio.h>

/* Helper: swap two integers */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Function: partition
 * Selects last element as pivot, places pivot in correct
 * sorted position, and moves smaller elements to its left
 * and greater elements to its right.
 *
 * Returns: final index of the pivot
 *
 * Time  : O(n)
 * Space : O(1)
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];   /* Choose last element as pivot */
    int i = low - 1;         /* Index of smaller element    */

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    /* Place pivot in its correct sorted position */
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

/* Function: quick_sort
 * Recursively sorts arr[low..high] using partitioning.
 *
 * Time  : O(n log n) average, O(n²) worst
 * Space : O(log n) average call stack
 */
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  /* Pivot index */

        quick_sort(arr, low, pi - 1);        /* Sort left half  */
        quick_sort(arr, pi + 1, high);       /* Sort right half */
    }
}

/* Helper: print array */
void print_array(int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d%s", arr[i], i < n - 1 ? ", " : " ");
    printf("]\n");
}

int main() {
    int arr[100], n;

    printf("========================================\n");
    printf("          QUICK SORT PROGRAM            \n");
    printf("========================================\n\n");

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid! Enter between 1 and 100.\n");
        return 1;
    }

    printf("Enter %d element(s): ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal Array : ");
    print_array(arr, n);

    quick_sort(arr, 0, n - 1);

    printf("Sorted Array   : ");
    print_array(arr, n);

    printf("\n========================================\n");

    return 0;
}