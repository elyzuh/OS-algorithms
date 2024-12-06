#include <stdio.h>

typedef struct {
    int pageNumber;
} PageFrame;

float hitRatio(int hitNum, int reference);
float hitFault(int faultNum, int reference);

int main() {
    int i, j, n, no, refStr[50], avail, fcount = 0, hitCount = 0;

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
    }

    j = 0; 
    printf("\nRef String\tPage Frames\t\tHit/Fault\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t", refStr[i]);
        avail = 0; 
     
        for (int k = 0; k < no; k++) {
            if (frames[k].pageNumber == refStr[i]) {
                avail = 1; 
                hitCount++;
                break;
            }
        }

        if (avail == 1) {
            for (int k = 0; k < no; k++) {
                if (frames[k].pageNumber != -1)
                    printf("%d\t", frames[k].pageNumber);
                else
                    printf("-\t");
            }
            printf("H\n");
        } else {
            frames[j].pageNumber = refStr[i];
            j = (j + 1) % no;
            fcount++;       
        
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

    return 0;
}

float hitRatio(int hitNum, int reference) {
    return ((float) hitNum / reference) * 100;
}

float hitFault(int faultNum, int reference) {
    return ((float) faultNum / reference) * 100;
}
