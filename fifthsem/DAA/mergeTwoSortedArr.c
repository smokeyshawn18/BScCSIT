/*
 * ============================================================
 *  OBJECTIVE:
 *   Write a program to merge two sorted arrays entered by
 *   the user into a single sorted array.
 * ============================================================
 *  MERGE TWO SORTED ARRAYS
 * ============================================================
 * THEORY:
 *   Merging two sorted arrays means combining them into one
 *   array that is also sorted, without using any sorting
 *   algorithm — by taking advantage of the fact that both
 *   input arrays are already individually sorted.
 *
 *   Two pointers (i and j) start at the beginning of each
 *   array. At every step, the smaller of the two current
 *   elements is picked and placed into the result array,
 *   and that pointer advances forward.
 *
 *   Once one array is exhausted, all remaining elements of
 *   the other array are copied directly into the result,
 *   since they are already in sorted order.
 *
 *   This is the same core merging step used internally by
 *   Merge Sort, but applied directly to two full arrays
 *   instead of two halves of a single array.
 *
 * TIME COMPLEXITY:
 *   O(n + m)  — Each element from both arrays is visited once
 *               where n = size of first array,
 *                     m = size of second array
 *
 * SPACE COMPLEXITY:
 *   O(n + m)  — A new result array of size n + m is required
 * ============================================================
 */

#include <stdio.h>

#define MAX_SIZE 100

/* Function: merge_sorted_arrays
 * Merges two sorted arrays a[n] and b[m] into result[n+m].
 *
 * Time  : O(n + m)
 * Space : O(n + m)
 */
void merge_sorted_arrays(int a[], int n, int b[], int m, int result[]) {
    int i = 0, j = 0, k = 0;

    /* Compare elements from both arrays, pick smaller one */
    while (i < n && j < m) {
        if (a[i] <= b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    /* Copy remaining elements of first array, if any */
    while (i < n)
        result[k++] = a[i++];

    /* Copy remaining elements of second array, if any */
    while (j < m)
        result[k++] = b[j++];
}

/* Helper: print array */
void print_array(int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d%s", arr[i], i < n - 1 ? ", " : " ");
    printf("]\n");
}

int main() {
    int a[MAX_SIZE], b[MAX_SIZE], result[2 * MAX_SIZE];
    int n, m;

    printf("========================================\n");
    printf("    MERGE TWO SORTED ARRAYS PROGRAM     \n");
    printf("========================================\n\n");

    /* Input: first array */
    printf("Enter number of elements in first array : ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid! Enter between 1 and %d.\n", MAX_SIZE);
        return 1;
    }

    printf("Enter %d sorted element(s) for first array : ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    /* Input: second array */
    printf("\nEnter number of elements in second array: ");
    scanf("%d", &m);

    if (m <= 0 || m > MAX_SIZE) {
        printf("Invalid! Enter between 1 and %d.\n", MAX_SIZE);
        return 1;
    }

    printf("Enter %d sorted element(s) for second array: ", m);
    for (int j = 0; j < m; j++)
        scanf("%d", &b[j]);

    /* Display both input arrays */
    printf("\nFirst Array    : ");
    print_array(a, n);

    printf("Second Array   : ");
    print_array(b, m);

    /* Merge and display result */
    merge_sorted_arrays(a, n, b, m, result);

    printf("Merged Array   : ");
    print_array(result, n + m);

    printf("\n========================================\n");

    return 0;
}