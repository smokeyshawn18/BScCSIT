#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int disk_size = 200;

int cmpfunc(const void *a, const void *b);

void SCAN(int arr[], int size, int head, char *direction)
{
    int seek_count = 0;
    int distance, cur_track;
    int left[size + 1], right[size + 1];  // +1 for including 0 or disk_size-1
    int left_count = 0, right_count = 0;

    // Add boundary based on direction
    if (strcmp(direction, "left") == 0)
        left[left_count++] = 0;
    else if (strcmp(direction, "right") == 0)
        right[right_count++] = disk_size - 1;

    // Divide into left and right lists
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < head)
            left[left_count++] = arr[i];
        if (arr[i] > head)
            right[right_count++] = arr[i];
    }

    // Sort the two sides
    qsort(left, left_count, sizeof(int), cmpfunc);
    qsort(right, right_count, sizeof(int), cmpfunc);

    int seek_sequence[size + 2]; // sequence order
    int sequence_count = 0;

    int run = 2;
    int initial_head = head;

    printf("\nHead movement sequence:\n");
    printf("%d", head); // starting point

    while (run--)
    {
        if (strcmp(direction, "left") == 0)
        {
            for (int i = left_count - 1; i >= 0; i--)
            {
                cur_track = left[i];
                seek_sequence[sequence_count++] = cur_track;
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
                printf(" -> %d", head);  // print movement
            }
            strcpy(direction, "right");
        }
        else if (strcmp(direction, "right") == 0)
        {
            for (int i = 0; i < right_count; i++)
            {
                cur_track = right[i];
                seek_sequence[sequence_count++] = cur_track;
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
                printf(" -> %d", head);  // print movement
            }
            strcpy(direction, "left");
        }
    }

    printf("\n\nTotal head movement (cylinders moved) = %d\n", seek_count);
    printf("Total seek operations = %d\n", seek_count); // same here
}

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
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

    char direction[10];
    printf("Enter the direction (left/right): ");
    scanf("%s", direction);

    SCAN(arr, n, head, direction);

    return 0;
}
