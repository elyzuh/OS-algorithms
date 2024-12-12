/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    C-Scan - IO Management Algorithm                                    *
*   Date:           12 / 03 / 24                                                        *
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int initialPosition;
    int requestQueue[MAX];
    int size;
    int diskSize; // Maximum disk size
} Disk;

void processRequestsCSCAN(Disk *disk);
void sortRequests(int arr[], int size);

int main(void) {
    system("CLS");
    Disk disk = {
        .initialPosition = 55, // Initial head position
        .requestQueue = {93, 176, 42, 148, 27, 14, 180}, // Requests
        .size = 7, // Number of requests
        .diskSize = 200 // Maximum disk size (tracks go from 0 to 399)
    };

    processRequestsCSCAN(&disk);

    return 0;
}

void processRequestsCSCAN(Disk *disk) {
    int totalHeadMovement = 0;
    int currentPosition = disk->initialPosition;

    // Sort the request queue in ascending order
    sortRequests(disk->requestQueue, disk->size);

    printf("\nProcessing Requests ::\n");

    // Track the sequence of movements for the Gantt chart
    printf("\nTrack Accessed and Head Movement:\n");
    printf("Tracks: ");
    
    // Process requests greater than or equal to the initial position
    for (int i = 0; i < disk->size; i++) {
        if (disk->requestQueue[i] >= currentPosition) {
            int movement = abs(currentPosition - disk->requestQueue[i]);
            printf("%d ", disk->requestQueue[i]);
            totalHeadMovement += movement;
            currentPosition = disk->requestQueue[i]; // Update current position
        }
    }

    // After processing all larger requests, move to the end of the disk
    int movementToEnd = abs(currentPosition - (disk->diskSize - 1));
    totalHeadMovement += movementToEnd; // Add the movement to the end
    printf("%d ", disk->diskSize - 1); // Print the end of the disk
    currentPosition = disk->diskSize - 1; // Now at the end of the disk

    // Process requests less than the initial position (after wrapping around)
    for (int i = 0; i < disk->size; i++) {
        if (disk->requestQueue[i] < disk->initialPosition) {
            int movement = abs(currentPosition - disk->requestQueue[i]);
            printf("%d ", disk->requestQueue[i]);
            totalHeadMovement += movement;
            currentPosition = disk->requestQueue[i]; // Update current position
        }
    }

    // Calculate the total seek time (in milliseconds)
    int seekTime = totalHeadMovement * 5; // Seek rate is 5ms per track

    // Output the total head movement and total seek time
    printf("\nTotal head movement (THM): %d tracks\n", totalHeadMovement);
    printf("Total seek time: %d ms\n\n", seekTime); // Display the total seek time in milliseconds
}

void sortRequests(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
