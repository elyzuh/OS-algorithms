#include <stdio.h>

typedef struct {
    int pageNumber;
} PageFrame;

float hitRatio(int hitNum, int reference);
float hitFault(int faultNum, int reference);
void firstInFirstOut(int refStr[], int n, int no);

int main() {
    int n, no, refStr[50];

    printf("\nENTER THE NUMBER OF PAGES:\n");
    scanf("%d", &n);

    printf("\nENTER THE PAGE NUMBERS:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &refStr[i]);
    }

    printf("\nENTER THE NUMBER OF FRAMES:\n");
    scanf("%d", &no);

    firstInFirstOut(refStr, n, no);

    return 0;
}

void firstInFirstOut(int refStr[], int n, int no) {
    PageFrame frames[no];
    int fcount = 0, hitCount = 0;
    int j = 0;

    // initialize frames to empty, -1
    for (int i = 0; i < no; i++) {
        frames[i].pageNumber = -1;
    }

    printf("\nRef String\tPage Frames\t\tHit/Fault\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t", refStr[i]);
        int avail = 0;

        // check if the current page is already in one of the frames
        for (int k = 0; k < no; k++) {
            if (frames[k].pageNumber == refStr[i]) {
                avail = 1;
                hitCount++;
                break;
            }
        }

        if (avail == 1) {
            // print the current frames and mark it as a hit
            for (int k = 0; k < no; k++) {
                if (frames[k].pageNumber != -1)
                    printf("%d\t", frames[k].pageNumber);
                else
                    printf("-\t");
            }
            printf("H\n");
        } else {
            // replace the oldest page (FIFO) and mark it as a fault
            frames[j].pageNumber = refStr[i];
            j = (j + 1) % no; // circular index for FIFO
            fcount++;

            // print the current frames and mark it as a fault
            for (int k = 0; k < no; k++) {
                if (frames[k].pageNumber != -1)
                    printf("%d\t", frames[k].pageNumber);
                else
                    printf("-\t");
            }
            printf("F\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", fcount);
    printf("Hit Ratio: %.2f%%\n", hitRatio(hitCount, n));
    printf("Fault Ratio: %.2f%%\n", hitFault(fcount, n));
}

float hitRatio(int hitNum, int reference) {
    return ((float) hitNum / reference) * 100;
}

float hitFault(int faultNum, int reference) {
    return ((float) faultNum / reference) * 100;
}
