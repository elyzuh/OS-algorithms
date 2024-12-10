/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    Shortest Remaining Time First - CPU Scheduling Algorithm            *
*                                                                                       *
*   Date:           11 / 25 / 24                                                        *
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;

void inputProcesses(Process processes[], int *processCount);
void calculateSRTF(Process processes[], int processCount);
void displayResults(Process processes[], int processCount);

int main() {
    system("CLS");
    int processCount;

    printf("Enter number of Processes: ");
    scanf("%d", &processCount);

    Process processes[processCount];

    inputProcesses(processes, &processCount);
    calculateSRTF(processes, processCount);
    displayResults(processes, processCount);

    return 0;
}

void inputProcesses(Process processes[], int *processCount) {
    for (int i = 0; i < *processCount; i++) {
        printf("\nEnter Process ID (e.g., A, B, C): ");
        scanf(" %c", &processes[i].processID);

        printf("Enter Arrival Time for %c: ", processes[i].processID);
        scanf("%d", &processes[i].arrivalTime);

        printf("Enter Burst Time for %c: ", processes[i].processID);
        scanf("%d", &processes[i].burstTime);

        processes[i].remainingTime = processes[i].burstTime; // initialize remaining time
    }
}

void calculateSRTF(Process processes[], int processCount) {
    int currentTime = 0, completed = 0;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed != processCount) {
        int smallest = -1;

        // find process with shortest remaining time that has arrived
        for (int i = 0; i < processCount; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (smallest == -1 || processes[i].remainingTime < processes[smallest].remainingTime) {
                    smallest = i;
                }
            }
        }

        if (smallest == -1) {
            currentTime++; // no process is ready; increment time
            continue;
        }

        // process the selected task for 1 unit of time
        processes[smallest].remainingTime--;
        currentTime++;

        // if the process finishes
        if (processes[smallest].remainingTime == 0) {
            completed++;
            processes[smallest].completionTime = currentTime;
            processes[smallest].turnaroundTime = processes[smallest].completionTime - processes[smallest].arrivalTime;
            processes[smallest].waitingTime = processes[smallest].turnaroundTime - processes[smallest].burstTime;

            totalWaitingTime += processes[smallest].waitingTime;
            totalTurnaroundTime += processes[smallest].turnaroundTime;
        }
    }
}

void displayResults(Process processes[], int processCount) {
    int totalTurnaroundTime = 0, totalWaitingTime = 0;

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
