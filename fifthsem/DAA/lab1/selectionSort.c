/*
 * ============================================================
 *  SELECTION SORT — User Input Version
 * ============================================================
 * THEORY:
 *   Finds the minimum element from the unsorted part
 *   and places it at the beginning, pass by pass.
 *
 * TIME COMPLEXITY:
 *   Best / Average / Worst : O(n²)
 *
 * SPACE COMPLEXITY:
 *   O(1)  — In-place sorting
 * ============================================================
 */

#include <stdio.h>

#define MAX_SIZE 100

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        if (min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}

void print_array(int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d%s", arr[i], i < n - 1 ? ", " : " ");
    printf("]\n");
}

int main() {
    int arr[MAX_SIZE], n;
    printf("SELECTION SORT PROGRAM\n");
    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid! Enter between 1 and %d.\n", MAX_SIZE);
        return 1;
    }

    printf("Enter %d element(s): ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal Array : ");
    print_array(arr, n);

    selection_sort(arr, n);

    printf("Sorted Array   : ");
    print_array(arr, n);


    return 0;
}