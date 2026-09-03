#include <stdio.h>

typedef struct {
    int page;
    int ref_bit; // reference bit
} Frame;

int main() {
    int pages[30], n, f, i, j, page_faults = 0, pointer = 0;
    Frame frames[10];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (i = 0; i < f; i++) {
        frames[i].page = -1;
        frames[i].ref_bit = 0;
    }

    printf("\nPage Reference String Processing (Second Chance):\n");

    for (i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in frames
        for (j = 0; j < f; j++) {
            if (frames[j].page == page) {
                frames[j].ref_bit = 1; // give second chance
                found = 1;
                break;
            }
        }

        // If not found, need replacement
        if (!found) {
            while (1) {
                if (frames[pointer].page == -1) { 
                    // Empty slot
                    frames[pointer].page = page;
                    frames[pointer].ref_bit = 0;
                    pointer = (pointer + 1) % f;
                    break;
                }
                else if (frames[pointer].ref_bit == 0) {
                    // Replace this page
                    frames[pointer].page = page;
                    frames[pointer].ref_bit = 0;
                    pointer = (pointer + 1) % f;
                    break;
                }
                else {
                    // Give second chance
                    frames[pointer].ref_bit = 0;
                    pointer = (pointer + 1) % f;
                }
            }
            page_faults++;
        }

        // Print current frame state
        printf("Page %d -> ", page);
        for (j = 0; j < f; j++) {
            if (frames[j].page != -1)
                printf("%d(%d) ", frames[j].page, frames[j].ref_bit);
            else
                printf("- ");
        }
        if (!found) printf(" (Page Fault)");
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", page_faults);

    return 0;
}
