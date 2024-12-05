#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;

void inputProcesses(Process processes[], int *processCount);
void calculateTimes(Process processes[], int processCount);
void displayResults(Process processes[], int processCount);

int main() {
    int processCount;

    printf("Enter Process Count: ");
    scanf("%d", &processCount);

    Process processes[processCount];

    inputProcesses(processes, &processCount);
    calculateTimes(processes, processCount);
    displayResults(processes, processCount);

    return 0;
}

void inputProcesses(Process processes[], int *processCount) {
    for (int i = 0; i < *processCount; i++) {
        printf("\nEnter Process ID (e.g., A, B, C): ");
        scanf(" %c", &processes[i].processID);
        
        printf("Arrival Time for %c: ", processes[i].processID);
        scanf("%d", &processes[i].arrivalTime);

        printf("CPU Burst Time for %c: ", processes[i].processID);
        scanf("%d", &processes[i].burstTime);
    }
}

void calculateTimes(Process processes[], int processCount) {
    int currentTime = 0;
    int completed = 0;
    int isCompleted[processCount];
    for (int i = 0; i < processCount; i++) {
        isCompleted[i] = 0;
    }

    while (completed != processCount) {
        int idx = -1;
        int shortestBurst = 9999;

        // Find the process with the shortest burst time that has arrived and is not completed
        for (int i = 0; i < processCount; i++) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (processes[i].burstTime < shortestBurst) {
                    shortestBurst = processes[i].burstTime;
                    idx = i;
                } else if (processes[i].burstTime == shortestBurst) {
                    // If burst times are the same, choose the process with earlier arrival time
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            processes[idx].completionTime = currentTime + processes[idx].burstTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

            currentTime = processes[idx].completionTime;
            isCompleted[idx] = 1;
            completed++;
        } else {
            currentTime++;
        }
    }
}

void displayResults(Process processes[], int processCount) {
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    printf("\nPROCESS ID\tArrival Time\tCPU Burst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
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
