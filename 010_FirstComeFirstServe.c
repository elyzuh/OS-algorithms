/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    First Come First Serve - IO Management Algorithm                    *
*                                                                                       *
*   Date:           12 / 3 / 24                                                         *
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void fcfsScheduling(int requests[], int n, int head);

int main() {
    int n, head;

    printf("Enter the number of I/O requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    fcfsScheduling(requests, n, head);

    return 0;
}

void fcfsScheduling(int requests[], int n, int head) {
    int seekTime = 0;
    int currentHead = head;

    printf("\nSequence of servicing requests:\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", requests[i]);
        seekTime += abs(requests[i] - currentHead);
        currentHead = requests[i];
    }
    printf("End\n");

    printf("Total Seek Time: %d\n", seekTime);
    printf("Average Seek Time: %.2f\n", (float)seekTime / n);
}
