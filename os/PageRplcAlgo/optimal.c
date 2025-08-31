#include <stdio.h>

int predict(int pages[], int frames[], int n, int index, int no_of_frames) {
    int res = -1, farthest = index, i, j;
    for (i = 0; i < no_of_frames; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        // If page never used in future, replace it
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30];
    int i, j, page_faults = 0, flag1, flag2, pos, index = 0;

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

    printf("\nPage Reference String Processing (Optimal):\n");

    for (i = 0; i < no_of_pages; i++) {
        flag1 = flag2 = 0;

        // Check if page is already in frame
        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        // If not in frame, try empty slot
        if (flag1 == 0) {
            for (j = 0; j < no_of_frames; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    page_faults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        // If no empty slot, replace using Optimal strategy
        if (flag2 == 0) {
            pos = predict(pages, frames, no_of_pages, i + 1, no_of_frames);
            frames[pos] = pages[i];
            page_faults++;
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
