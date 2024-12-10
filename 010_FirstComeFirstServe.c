/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    First Come First Serve - IO Management Algorithm                    *
*                                                                                       *
*   Date:           12 / 3 / 24                                                         *
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define TRACK_SIZE 400  //,maximum size of the disk track (0 to TRACK_SIZE - 1)
#define SEEK_RATE 5     // time taken to move the disk head one track (in milliseconds)

void fcfsScheduling(int requests[], int n, int head);

int main() {
    int n, head;

    // input the number of I/O requests
    printf("Enter the number of I/O requests: ");
    scanf("%d", &n);

    int requests[n];

    // input the requested track positions and validate their range
    printf("Enter the requests (range 0-%d):\n", TRACK_SIZE - 1);
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0 || requests[i] >= TRACK_SIZE) { 
            printf("Invalid request: %d. Requests must be between 0 and %d.\n", requests[i], TRACK_SIZE - 1);
            return 1;  
        }
    }

    printf("Enter the initial position of the disk head (range 0-%d): ", TRACK_SIZE - 1);
    scanf("%d", &head);
    if (head < 0 || head >= TRACK_SIZE) { // Validate head position
        printf("Invalid head position. It must be between 0 and %d.\n", TRACK_SIZE - 1);
        return 1;
    }

    fcfsScheduling(requests, n, head);

    return 0;
}

void fcfsScheduling(int requests[], int n, int head) {
    int seekTime = 0;      // total seek time (head movement)
    int currentHead = head; // current position of the disk head

    printf("\nSequence of servicing requests:\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", requests[i]);  // display the request being serviced
        seekTime += abs(requests[i] - currentHead);  // calculate the distance moved by the disk head
        currentHead = requests[i];  // update the current position of the disk head
    }
    printf("End\n");

    printf("\nTotal Head Movement: %d\n", seekTime);                           
    printf("Total Seek Time (THM * Seek Rate): %d ms\n", seekTime * SEEK_RATE); 
    printf("Average Seek Time: %.2f ms\n", (float)(seekTime * SEEK_RATE) / n); 
}
