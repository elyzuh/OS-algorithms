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

void processRequestsCLOOK(Disk *disk);
void sortRequests(int arr[], int size);

int main(void) {
    system("CLS");
    Disk disk = {
        .initialPosition = 256, // Initial head position
        .requestQueue = {46, 56, 276, 48, 236, 338, 112}, // Requests
        .size = 7, // Number of requests
        .diskSize = 400 // Maximum disk size (tracks go from 0 to 399)
    };

    processRequestsCLOOK(&disk);

    return 0;
}

void processRequestsCLOOK(Disk *disk) {
    int totalHeadMovement = 0;
    int currentPosition = disk->initialPosition;
    int totalSeekTime = 0; // Variable to calculate the total seek time
    int seekRate = 5; // Seek rate of 5ms per track movement

    // Sort the request queue in ascending order
    sortRequests(disk->requestQueue, disk->size);

    printf("\nProcessing Requests ::\n");

    // Track the sequence of movements for the Gantt chart
    printf("\nTrack Accessed, Head Movement and Seek Time:\n");
    printf("Tracks: ");
    
    // Process requests greater than or equal to the initial position
    for (int i = 0; i < disk->size; i++) {
        if (disk->requestQueue[i] >= currentPosition) {
            int movement = abs(currentPosition - disk->requestQueue[i]);
            totalHeadMovement += movement;
            totalSeekTime += movement * seekRate; // Add the seek time for this movement
            printf("\n%d (Seek Time: %d ms) ", disk->requestQueue[i], movement * seekRate);
            currentPosition = disk->requestQueue[i]; // Update current position
        }
    }

    // After processing all larger requests, move to the end of the disk
    int nextRequestMovement = 0;
    for (int i = 0; i < disk->size; i++) {
        if (disk->requestQueue[i] > currentPosition) {
            nextRequestMovement = abs(currentPosition - disk->requestQueue[i]);
            break;
        }
    }

    totalHeadMovement += nextRequestMovement;
    totalSeekTime += nextRequestMovement * seekRate; // Add the seek time for this movement
    currentPosition += nextRequestMovement; // Move to the next request in the sorted order
    printf("\n%d (Seek Time: %d ms) ", currentPosition, nextRequestMovement * seekRate); // Print the final movement

    // Process requests less than the initial position (after wrapping around)
    for (int i = 0; i < disk->size; i++) {
        if (disk->requestQueue[i] < disk->initialPosition) {
            int movement = abs(currentPosition - disk->requestQueue[i]);
            totalHeadMovement += movement;
            totalSeekTime += movement * seekRate; // Add the seek time for this movement
            printf("\n%d (Seek Time: %d ms) ", disk->requestQueue[i], movement * seekRate);
            currentPosition = disk->requestQueue[i]; // Update current position
        }
    }

    // Output the total head movement and total seek time
    printf("\nTotal head movement (THM): %d tracks\n", totalHeadMovement);
    printf("Total seek time: %d ms\n\n", totalSeekTime); // Display total seek time in milliseconds
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
