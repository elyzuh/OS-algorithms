/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    Least Recently Used - Page Replacement Algorithm                    *
*   Date:           12 / 3 / 24                                                         *
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pageNumber;
    int lastUsed;
} PageFrame;

float hitRatio(int hitNum, int reference);
float hitFault(int faultNum, int reference);
void leastRecentlyUsed(int refStr[], int n, int no);

int main() {
    system("CLS");
    int n, no, refStr[50];

    printf("\nENTER THE NUMBER OF PAGES:\n");
    scanf("%d", &n);

    printf("\nENTER THE PAGE NUMBERS:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &refStr[i]);
    }

    printf("\nENTER THE NUMBER OF FRAMES:\n");
    scanf("%d", &no);

    leastRecentlyUsed(refStr, n, no);

    return 0;
}

void leastRecentlyUsed(int refStr[], int n, int no) {
    PageFrame frames[no];
    int fcount = 0, hitCount = 0, time = 0;

    for (int i = 0; i < no; i++) {
        frames[i].pageNumber = -1;
        frames[i].lastUsed = -1;
    }

    printf("\nRef String\tPage Frames\t\tHit/Fault\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t", refStr[i]);
        int avail = 0;

        // check if the current page is already in one of the frames
        for (int j = 0; j < no; j++) {
            if (frames[j].pageNumber == refStr[i]) {
                avail = 1;
                frames[j].lastUsed = time++; //update last used time
                hitCount++;
                break;
            }
        }

        if (avail == 1) {
            //print current frames and mark it as a hit
            for (int j = 0; j < no; j++) {
                if (frames[j].pageNumber != -1)
                    printf("%d\t", frames[j].pageNumber);
                else
                    printf("-\t");
            }
            printf("H\n");
        } else {
            //find the least recently used page (LRU)
            int lruIndex = 0;
            int minTime = frames[0].lastUsed;

            for (int j = 1; j < no; j++) {
                if (frames[j].lastUsed < minTime) {
                    minTime = frames[j].lastUsed;
                    lruIndex = j;
                }
            }

            //replace the LRU page with the current page
            frames[lruIndex].pageNumber = refStr[i];
            frames[lruIndex].lastUsed = time++;
            fcount++; // Increment fault count

            //print current frames and mark it as a fault
            for (int j = 0; j < no; j++) {
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
}

float hitRatio(int hitNum, int reference) {
    return ((float) hitNum / reference) * 100;
}

float hitFault(int faultNum, int reference) {
    return ((float) faultNum / reference) * 100;
}
