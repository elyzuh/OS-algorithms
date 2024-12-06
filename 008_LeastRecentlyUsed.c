/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    Least Recently Used - Page Replacement Algorithm                    *
*                                                                                       *
*   Date:           12 / 3 / 24                                                         *
****************************************************************************************/

#include <stdio.h>

typedef struct {
    int pageNumber;
    int lastUsed;
} PageFrame;

float hitRatio(int hitNum, int reference);
float hitFault(int faultNum, int reference);

int main() {
    int i, j, n, no, refStr[50], fcount = 0, hitCount = 0, time = 0;

    printf("\nENTER THE NUMBER OF PAGES:\n");
    scanf("%d", &n);

    printf("\nENTER THE PAGE NUMBERS:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &refStr[i]);
    }

    printf("\nENTER THE NUMBER OF FRAMES:\n");
    scanf("%d", &no);

    PageFrame frames[no];
    
    for (i = 0; i < no; i++) {
        frames[i].pageNumber = -1;
        frames[i].lastUsed = -1;
    }

    printf("\nRef String\tPage Frames\t\tHit/Fault\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t", refStr[i]);
        int avail = 0;

        for (j = 0; j < no; j++) {
            if (frames[j].pageNumber == refStr[i]) {
                avail = 1;
                frames[j].lastUsed = time++;
                hitCount++;              
                break;
            }
        }

        if (avail == 1) {
            for (j = 0; j < no; j++) {
                if (frames[j].pageNumber != -1)
                    printf("%d\t", frames[j].pageNumber);
                else
                    printf("-\t");
            }
            printf("H\n");
        } else {
    
            int lruIndex = 0;
            int minTime = frames[0].lastUsed;

            for (j = 1; j < no; j++) {
                if (frames[j].lastUsed < minTime) {
                    minTime = frames[j].lastUsed;
                    lruIndex = j;
                }
            }

            frames[lruIndex].pageNumber = refStr[i];
            frames[lruIndex].lastUsed = time++;
            fcount++; // Increment fault count

            for (j = 0; j < no; j++) {
                if (frames[j].pageNumber != -1)
                    printf("%d\t", frames[j].pageNumber);
                else
                    printf("-\t");
            }
            printf("F\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", fcount);
    printf("Hit Ratio: %.2f%%\n", hitRatio(hitCount, n));
    printf("Fault Ratio: %.2f%%\n", hitFault(fcount, n));
    return 0;
}

float hitRatio(int hitNum, int reference) {
    return ((float) hitNum / reference) * 100;
}

float hitFault(int faultNum, int reference) {
    return ((float) faultNum / reference) * 100;
}
