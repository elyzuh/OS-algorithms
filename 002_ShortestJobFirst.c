/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    Shortest Job First - CPU Scheduling Algorithm                       *
*   Date:           11 / 08 / 24                                                        *
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char processID;       // Identifier for the process
    int arrivalTime;      // Time at which the process arrives
    int burstTime;        // CPU burst time needed for the process
    int completionTime;   // Time when the process is completed
    int turnaroundTime;   // Total time taken from arrival to completion
    int waitingTime;      // Time the process spends waiting in the ready queue
} Process;

void inputProcesses(Process processes[], int *processCount); // inputs process details from the user
void calculateTimes(Process processes[], int processCount);  // calculates the scheduling metrics
void displayResults(Process processes[], int processCount);  // displays the final results

int main() {
    system("CLS");
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
    int currentTime = 0;    // curr time
    int completed = 0;      // # of processes completed
    int isCompleted[processCount]; //array to track if a process is completed

    //initialize all processes as not completed
    for (int i = 0; i < processCount; i++) {
        isCompleted[i] = 0;
    }

    while (completed != processCount) {
        int idx = -1;       
        int shortestBurst = 9999;

        // find the process with the shortest burst time that has arrived and is not completed
        for (int i = 0; i < processCount; i++) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (processes[i].burstTime < shortestBurst) {
                    shortestBurst = processes[i].burstTime;
                    idx = i;
                } else if (processes[i].burstTime == shortestBurst) {
                    // choose process with earlier arrival time
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        // if a valid process is found, execute it
        if (idx != -1) {
            // calculate completion time for the selected process
            processes[idx].completionTime = currentTime + processes[idx].burstTime;

            // calculate turnaround time and waiting time
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

            //update current time and mark the process as completed
            currentTime = processes[idx].completionTime;
            isCompleted[idx] = 1;
            completed++; //increment the count of completed processes
        } else {
            // if no process is ready, increment the current time
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
