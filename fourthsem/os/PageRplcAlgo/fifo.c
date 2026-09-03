#include <stdio.h>

int main() {
    int i, j, k, n, f, pf = 0, count = 0;
    int pages[30], frames[10];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames as empty
    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nPage Reference String Processing (FIFO):\n");
    for (i = 0; i < n; i++) {
        int flag = 0;

        // Check if page is already in frame
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        // If page not found, replace using FIFO
        if (flag == 0) {
            frames[count % f] = pages[i];
            count++;
            pf++;
        }

        // Print current frame status
        printf("Page %d -> ", pages[i]);
        for (k = 0; k < f; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }
        if (flag == 0)
            printf(" (Page Fault)");
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pf);

    return 0;
}
