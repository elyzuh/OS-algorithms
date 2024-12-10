/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    Round Robin - CPU Scheduling Algorithm                              *
*                                                                                       *
*   Date:           12 / 07 / 24                                                        *
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;

void roundRobinScheduling(Process processes[], int processCount, int timeQuantum);
void displayResults(Process processes[], int processCount);

int main() {
    system("cls");
    int processCount = 5;
    int timeQuantum = 4;

    Process processes[] = {
        {'A', 0, 10, 10, 0, 0, 0},
        {'B', 2,  5,  5, 0, 0, 0},
        {'C', 3,  2,  2, 0, 0, 0},
        {'D', 5, 20, 20, 0, 0, 0},
        {'E', 8, 10, 10, 0, 0, 0}
    };

    roundRobinScheduling(processes, processCount, timeQuantum);
    displayResults(processes, processCount);

    return 0;
}

void roundRobinScheduling(Process processes[], int processCount, int timeQuantum) {
    int currentTime = 0;
    int completed = 0;
    bool isInQueue[processCount];
    int queue[processCount];
    int front = 0, rear = 0;

    for (int i = 0; i < processCount; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        isInQueue[i] = false;
    }

    // Add the first process to the queue
    queue[rear++] = 0;
    isInQueue[0] = true;

    while (completed < processCount) {
        if (front < rear) {
            int currentIdx = queue[front++ % processCount]; // Use modulo for circular queue
            Process *current = &processes[currentIdx];

            if (current->arrivalTime <= currentTime) {
                int timeSlice = current->remainingTime > timeQuantum ? timeQuantum : current->remainingTime;
                current->remainingTime -= timeSlice;
                currentTime += timeSlice;

                // Add new arrivals to the queue
                for (int i = 0; i < processCount; i++) {
                    if (!isInQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                        queue[rear++ % processCount] = i; // Use modulo for circular queue
                        isInQueue[i] = true;
                    }
                }

                if (current->remainingTime == 0) {
                    current->completionTime = currentTime;
                    current->turnaroundTime = current->completionTime - current->arrivalTime;
                    current->waitingTime = current->turnaroundTime - current->burstTime;
                    completed++;
                } else {
                    queue[rear++ % processCount] = currentIdx; // Re-add to the queue if not finished
                }
            } else {
                currentTime++;
                queue[rear++ % processCount] = currentIdx; // Re-add to the queue if it hasn't arrived yet
            }
        } else {
            currentTime++; // Idle time if no process is ready
        }

        // Debugging output to check queue state and current time
        printf("Current Time: %d\n", currentTime);
        printf("Queue State: ");
        for (int i = front; i < rear; i++) {
            printf("%c ", processes[queue[i % processCount]].processID);
        }
        printf("\n\n");
    }
}

void displayResults(Process processes[], int processCount) {
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    printf("\nPROCESS ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < processCount; i++) {
        printf("    %c\t\t     %d\t\t     %d\t\t     %d\t\t     %d\t\t    %d\n", 
               processes[i].processID, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               processes[i].completionTime, 
               processes[i].turnaroundTime, 
               processes[i].waitingTime);

        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    double avgTurnaroundTime = (double)totalTurnaroundTime / processCount;
    double avgWaitingTime = (double)totalWaitingTime / processCount;

    printf("\nAverage Turnaround Time: %.2f", avgTurnaroundTime);
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
}
