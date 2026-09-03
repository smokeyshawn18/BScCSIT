#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int seek_rate = 5; // assume 5 ms per cylinder movement

// Compare function for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void LOOK(int arr[], int n, int head, char *direction)
{
    int seek_count = 0;
    int distance, cur_track;
    int left[n], right[n];
    int left_size = 0, right_size = 0;

    // Divide requests into left and right
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < head)
            left[left_size++] = arr[i];
        if (arr[i] > head)
            right[right_size++] = arr[i];
    }

    // Sort both sides
    qsort(left, left_size, sizeof(int), compare);
    qsort(right, right_size, sizeof(int), compare);

    int seek_sequence[n];
    int seq_index = 0;

    // Run two passes (one in given direction, then reverse)
    int run = 2;
    while (run--)
    {
        if (strcmp(direction, "left") == 0)
        {
            for (int i = left_size - 1; i >= 0; i--)
            {
                cur_track = left[i];
                seek_sequence[seq_index++] = cur_track;
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            strcpy(direction, "right");
        }
        else if (strcmp(direction, "right") == 0)
        {
            for (int i = 0; i < right_size; i++)
            {
                cur_track = right[i];
                seek_sequence[seq_index++] = cur_track;
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            strcpy(direction, "left");
        }
    }

    // Print sequence
    printf("\nSeek Sequence: ");
    for (int i = 0; i < seq_index; i++)
        printf("%d ", seek_sequence[i]);

    printf("\nTotal Head Movement (cylinders) = %d", seek_count);
    printf("\nTotal Seek Time = %d ms\n", seek_count * seek_rate);
}

int main()
{
    int n, head;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    char direction[10];
    printf("Enter the initial direction (left/right): ");
    scanf("%s", direction);

    LOOK(arr, n, head, direction);

    return 0;
}
