#include <stdio.h>
#include <stdlib.h>

struct head
{
    int num;   // request
    int flag;  // 0 = not served, 1 = served
};

int main()
{
    struct head h[33];
    int array_1[33], array_2[33];
    int count = 0, j, x, limit, minimum, location, disk_head, sum = 0;

    printf("\nEnter total number of requests: ");
    scanf("%d", &limit);

    printf("Enter initial position of disk head: ");
    scanf("%d", &disk_head);

    printf("Enter elements of disk request queue: ");
    while (count < limit)
    {
        scanf("%d", &h[count].num);
        h[count].flag = 0; // mark unvisited
        count++;
    }

    printf("\nHead movement sequence: %d", disk_head);

    // Process all requests
    for (count = 0; count < limit; count++)
    {
        x = 0;
        minimum = 0;
        location = 0;

        // find nearest request
        for (j = 0; j < limit; j++)
        {
            if (h[j].flag == 0)
            {
                if (x == 0)
                {
                    array_1[j] = abs(disk_head - h[j].num);
                    minimum = array_1[j];
                    location = j;
                    x++;
                }
                else
                {
                    array_1[j] = abs(disk_head - h[j].num);
                }
                if (minimum > array_1[j])
                {
                    minimum = array_1[j];
                    location = j;
                }
            }
        }

        // serve this request
        h[location].flag = 1;
        array_2[count] = abs(h[location].num - disk_head);
        sum += array_2[count];
        disk_head = h[location].num;

        printf(" -> %d", disk_head); // print movement
    }

    printf("\nTotal Head Movement (Seek Time): %d\n", sum);

    return 0;
}
