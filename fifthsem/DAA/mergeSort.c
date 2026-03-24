/*
 * ============================================================
 *  OBJECTIVE:
 *   Write a program to sort an array of integers entered by
 *   the user using the Merge Sort algorithm.
 * ============================================================
 *  MERGE SORT
 * ============================================================
 * THEORY:
 *   Merge Sort is a Divide and Conquer algorithm that splits
 *   the array into two halves, recursively sorts each half,
 *   and then merges the two sorted halves into one sorted array.
 *
 *   The merging step compares elements from both halves one
 *   by one and places the smaller element into the result,
 *   ensuring the combined array remains in sorted order.
 *
 *   It guarantees O(n log n) performance in all cases, making
 *   it more reliable than Bubble, Selection, or Insertion Sort
 *   for large datasets where worst-case performance matters.
 *
 *   Works like splitting a deck of cards into two piles,
 *   sorting each pile, then interleaving them back together
 *   by always picking the smaller top card from either pile.
 *
 * TIME COMPLEXITY:
 *   Best Case    : O(n log n)
 *   Average Case : O(n log n)
 *   Worst Case   : O(n log n)
 *
 * SPACE COMPLEXITY:
 *   O(n)  — Requires a temporary array for merging
 *
 * STABLE SORT: YES
 * ============================================================
 */

#include <stdio.h>

/* Function: merge
 * Merges two sorted subarrays arr[left..mid] and arr[mid+1..right]
 * into a single sorted subarray.
 *
 * Time  : O(n)
 * Space : O(n)  — temporary arrays
 */
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    /* Temporary arrays */
    int L[n1], R[n2];

    /* Copy data to temporary arrays */
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    /* Merge the two halves back into arr */
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    /* Copy remaining elements */
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

/* Function: merge_sort
 * Recursively divides and sorts arr[left..right].
 *
 * Time  : O(n log n)
 * Space : O(n)
 */
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;   /* Avoids overflow */

        merge_sort(arr, left, mid);             /* Sort left half  */
        merge_sort(arr, mid + 1, right);        /* Sort right half */
        merge(arr, left, mid, right);           /* Merge both      */
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
    printf("          MERGE SORT PROGRAM            \n");
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

    merge_sort(arr, 0, n - 1);

    printf("Sorted Array   : ");
    print_array(arr, n);

    printf("\n========================================\n");

    return 0;
}