#include <stdio.h>
#include <stdlib.h>

int disk_size = 200;  // total disk size (0 to disk_size-1)
int seek_rate = 5;    // assume 5 ms per cylinder movement

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void CSCAN(int arr[], int n, int head)
{
    int seek_count = 0;
    int distance, cur_track;
    int left[n + 1], right[n + 1];
    int left_count = 0, right_count = 0;

    // Add end values
    left[left_count++] = 0;
    right[right_count++] = disk_size - 1;

    // Divide requests into left and right of head
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < head)
            left[left_count++] = arr[i];
        else if (arr[i] > head)
            right[right_count++] = arr[i];
    }

    // Sort both sides
    qsort(left, left_count, sizeof(int), cmpfunc);
    qsort(right, right_count, sizeof(int), cmpfunc);

    // Store seek sequence
    int seek_sequence[n + 2];
    int seq_index = 0;

    // Service requests to the right of head
    for (int i = 0; i < right_count; i++)
    {
        cur_track = right[i];
        seek_sequence[seq_index++] = cur_track;
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    // Jump to beginning (circular)
    head = 0;
    seek_count += (disk_size - 1);
    seek_sequence[seq_index++] = 0;

    // Service requests to the left
    for (int i = 0; i < left_count; i++)
    {
        cur_track = left[i];
        seek_sequence[seq_index++] = cur_track;
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
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
    printf("Enter requests: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the head position: ");
    scanf("%d", &head);

    CSCAN(arr, n, head);

    return 0;
}
