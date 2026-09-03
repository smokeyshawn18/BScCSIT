#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int seek_rate = 5; // assume 5 ms per cylinder

// Compare function for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void CLOOK(int arr[], int n, int head, char *direction)
{
    int seek_count = 0;
    int distance, cur_track;
    int left[n], right[n];
    int left_count = 0, right_count = 0;

    // Divide requests into left and right of head
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < head)
            left[left_count++] = arr[i];
        else if (arr[i] > head)
            right[right_count++] = arr[i];
    }

    // Sort both sides
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    int seek_sequence[n];
    int seq_index = 0;

    // If moving right
    if (strcmp(direction, "right") == 0)
    {
        // Service the right side
        for (int i = 0; i < right_count; i++)
        {
            cur_track = right[i];
            seek_sequence[seq_index++] = cur_track;
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }

        // Jump to the leftmost request
        if (left_count > 0)
        {
            seek_count += abs(head - left[0]);
            head = left[0];

            // Service left side
            for (int i = 0; i < left_count; i++)
            {
                cur_track = left[i];
                seek_sequence[seq_index++] = cur_track;
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
        }
    }
    else // Moving left
    {
        // Service left side
        for (int i = left_count - 1; i >= 0; i--)
        {
            cur_track = left[i];
            seek_sequence[seq_index++] = cur_track;
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }

        // Jump to the rightmost request
        if (right_count > 0)
        {
            seek_count += abs(head - right[0]);
            head = right[0];

            // Service right side
            for (int i = 0; i < right_count; i++)
            {
                cur_track = right[i];
                seek_sequence[seq_index++] = cur_track;
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
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
    printf("Enter the direction of head movement (left/right): ");
    scanf("%s", direction);

    CLOOK(arr, n, head, direction);

    return 0;
}
