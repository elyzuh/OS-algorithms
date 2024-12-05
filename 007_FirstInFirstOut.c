/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    First In First Out - Page Replacement Algorithm                     *
*                                                                                       *
*   Date:           12 / 3 / 24                                                         *
****************************************************************************************/

#include <stdio.h>

typedef struct {
    int pageNumber;
} PageFrame;

int main() {
    int i, j, n, no, refStr[50], avail, fcount = 0;

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

    return 0;
}
