/*
 * ============================================================
 *  OBJECTIVE:
 *   Write a program to sort an array of integers entered by
 *   the user using the Bubble Sort algorithm.
 * ============================================================
 *  BUBBLE SORT
 * ============================================================
 * THEORY:
 *   Bubble Sort repeatedly steps through the array, compares
 *   adjacent elements, and swaps them if they are in the wrong
 *   order. With each full pass, the largest unsorted element
 *   "bubbles up" to its correct position at the end.
 *
 *   The algorithm continues making passes until no swaps are
 *   needed in a complete pass, meaning the array is sorted.
 *   An optimized version uses a flag to detect early completion
 *   when the array becomes sorted before all passes finish.
 *
 * TIME COMPLEXITY:
 *   Best Case    : O(n)    — Already sorted (with swap flag)
 *   Average Case : O(n²)
 *   Worst Case   : O(n²)   — Reverse sorted array
 *
 * SPACE COMPLEXITY:
 *   O(1)  — In-place sorting, no extra array needed
 *
 * STABLE SORT: YES
 * ============================================================
 */

#include <stdio.h>

/* Helper: swap two integers */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Function: bubble_sort
 * Sorts array 'arr' of size 'n' in ascending order.
 *
 * Time  : O(n²) worst/average, O(n) best
 * Space : O(1)
 */
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;   /* Optimization flag */

        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        /* If no swaps occurred, array is already sorted */
        if (swapped == 0)
            break;
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
    printf("          BUBBLE SORT PROGRAM           \n");
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

    bubble_sort(arr, n);

    printf("Sorted Array   : ");
    print_array(arr, n);

    printf("\n========================================\n");

    return 0;
}