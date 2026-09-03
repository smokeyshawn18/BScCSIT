#include <stdio.h>

int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30];
    int counter = 0, time[10], flag1, flag2, pos, i, j, page_faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    printf("Enter the reference string: ");
    for (i = 0; i < no_of_pages; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    // Initialize frames
    for (i = 0; i < no_of_frames; i++)
        frames[i] = -1;

    printf("\nPage Reference String Processing (LRU):\n");

    for (i = 0; i < no_of_pages; i++) {
        flag1 = flag2 = 0;

        // Check if page already in frame
        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter; // Update recent use
                flag1 = flag2 = 1;
                break;
            }
        }

        // If not in frame
        if (flag1 == 0) {
            for (j = 0; j < no_of_frames; j++) {
                if (frames[j] == -1) {  // Empty slot available
                    counter++;
                    page_faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        // If no empty slot, replace LRU page
        if (flag2 == 0) {
            pos = findLRU(time, no_of_frames);
            counter++;
            page_faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        // Print current frame state
        printf("Page %d -> ", pages[i]);
        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        if (flag1 == 0)
            printf(" (Page Fault)");
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", page_faults);

    return 0;
}
