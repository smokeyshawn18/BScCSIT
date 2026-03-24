#include <stdio.h>

/* Function: insertion_sort */
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/* Helper: print array */
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[100];
    int n;

    printf("=== INSERTION SORT ===\n");

    /* Take size input */
    printf("Enter number of elements: ");
    scanf("%d", &n);

    /* Take array input */
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Before: ");
    print_array(arr, n);

    insertion_sort(arr, n);

    printf("After : ");
    print_array(arr, n);

    return 0;
}