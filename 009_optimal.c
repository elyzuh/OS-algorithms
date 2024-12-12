/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    Optimal Page Replacement Algorithm                                  *
*   Date:           12 / 10 / 24                                                        *
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void optimalPageReplacement(int refStr[], int n, int no);
float hitRatio(int hitNum, int reference);
float faultRatio(int faultNum, int reference);

int main() {
    system("CLS");
    int n = 14, no = 3;
    int refStr[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1};

    printf("Page Reference String: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", refStr[i]);
    }
    printf("\n\nNumber of Frames: %d\n", no);

    optimalPageReplacement(refStr, n, no);

    return 0;
}

void optimalPageReplacement(int refStr[], int n, int no) {
    int frames[no];
    int fcount = 0, hitCount = 0;

    for (int i = 0; i < no; i++) {
        frames[i] = -1; // Initialize frame slots as empty
    }

    printf("\nRef_S\tPages\tH/F\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t", refStr[i]);
        bool hit = false;

        // Check if page is already in a frame (hit)
        for (int j = 0; j < no; j++) {
            if (frames[j] == refStr[i]) {
                hit = true;
                hitCount++;
                break;
            }
        }

        if (!hit) {
            // Page fault: Find the page to replace
            int replaceIndex = -1;
            int farthest = i + 1;

            for (int j = 0; j < no; j++) {
                int nextUse = n;
                for (int k = i + 1; k < n; k++) {
                    if (frames[j] == refStr[k]) {
                        nextUse = k;
                        break;
                    }
                }
                if (nextUse > farthest) {
                    farthest = nextUse;
                    replaceIndex = j;
                }

                // If a frame isn't going to be used again, choose it
                if (nextUse == n) {
                    replaceIndex = j;
                    break;
                }
            }

            // Replace the page in the frame
            if (replaceIndex == -1) {
                replaceIndex = 0; // Default to the first frame if no replacement index found
            }
            frames[replaceIndex] = refStr[i];
            fcount++;
        }

        // Print frame state horizontally
        for (int j = 0; j < no; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf(hit ? "\tH\n" : "\tF\n");
    }

    printf("\nTotal Page Faults: %d\n", fcount);
    printf("Hit Ratio: %.2f%%\n", hitRatio(hitCount, n));
    printf("Fault Ratio: %.2f%%\n", faultRatio(fcount, n));
}

float hitRatio(int hitNum, int reference) {
    return ((float)hitNum / reference) * 100;
}

float faultRatio(int faultNum, int reference) {
    return ((float)faultNum / reference) * 100;
}
