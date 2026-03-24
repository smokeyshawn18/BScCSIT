// *
//  * ============================================================
//  *  INSERTION SORT
//  * ============================================================
//  * THEORY:
//  *   Insertion Sort builds a sorted sub-array one element at a
//  *   time. It picks each element from the unsorted part and
//  *   "inserts" it into its correct position in the sorted part,
//  *   shifting larger elements one position to the right.
//  *
//  *   Works like sorting a hand of playing cards:
//  *   - Start with one card (sorted).
//  *   - Pick the next card and slide it into the correct spot.
//  *   - Repeat until all cards are sorted.
//  *
//  * TIME COMPLEXITY:
//  *   Best Case    : O(n)       — Already sorted array
//  *   Average Case : O(n²)
//  *   Worst Case   : O(n²)      — Reverse sorted array
//  *
//  * SPACE COMPLEXITY:
//  *   O(1)  — In-place sorting, no extra array needed
//  *
//  * STABLE SORT: YES
//  * ============================================================
//  */
 
#include <stdio.h>
 
/* Function: insertion_sort
 * Sorts array 'arr' of size 'n' in ascending order.
 *
 * Time  : O(n²) worst/average, O(n) best
 * Space : O(1)
 */
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];       /* Element to be inserted */
        int j = i - 1;
 
        /* Shift elements greater than key one position right */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;       /* Place key in correct position */
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
 
    printf("=== INSERTION SORT ===\n");
    printf("Before: ");
    print_array(arr, n);
 
    insertion_sort(arr, n);
 
    printf("After : ");
    print_array(arr, n);
 
    return 0;
}
 