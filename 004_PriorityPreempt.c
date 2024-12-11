/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    Priority Preemptive - CPU Scheduling Algorithm                      *
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
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;

// Min-Heap for priority management
typedef struct {
    Process *heap;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createPriorityQueue(int capacity);
void insertProcess(PriorityQueue *pq, Process p);
Process extractHighestPriority(PriorityQueue *pq);
bool isEmpty(PriorityQueue *pq);
void minHeapify(PriorityQueue *pq, int idx);

void priorityPreemptiveScheduling(Process processes[], int processCount);
void displayResults(Process processes[], int processCount);
void freePriorityQueue(PriorityQueue *pq);

int main() {
    system("CLS");
    int processCount = 5;

    Process processes[] = {
        {'A', 0, 10, 10, 3, 0, 0, 0},
        {'B', 2,  5,  5, 2, 0, 0, 0},
        {'C', 3,  2,  2, 5, 0, 0, 0},
        {'D', 5, 20, 20, 1, 0, 0, 0},
        {'E', 8, 10, 10, 4, 0, 0, 0}
    };

    priorityPreemptiveScheduling(processes, processCount);
    displayResults(processes, processCount);

    return 0;
}

void priorityPreemptiveScheduling(Process processes[], int processCount) {
    PriorityQueue *pq = createPriorityQueue(processCount);
    int currentTime = 0;
    int completed = 0;
    bool isAdded[processCount];

    for (int i = 0; i < processCount; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        isAdded[i] = false;
    }

    while (completed < processCount) {
        // Add all processes that arrive at currentTime to the queue
        for (int i = 0; i < processCount; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && !isAdded[i]) {
                insertProcess(pq, processes[i]);
                isAdded[i] = true;
            }
        }

        if (!isEmpty(pq)) {
            Process current = extractHighestPriority(pq);

            // Execute the process slice for 1 time unit
            for (int i = 0; i < processCount; i++) {
                if (processes[i].processID == current.processID) {
                    processes[i].remainingTime--;

                    // If completed, mark completion metrics
                    if (processes[i].remainingTime == 0) {
                        processes[i].completionTime = currentTime + 1;
                        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                        completed++;
                    } else {
                        // Reinsert only if there's remaining time
                        insertProcess(pq, processes[i]);
                    }
                }
            }

            currentTime++; // Only increment after execution
        } else {
            // No processes ready, so simulate idle time
            currentTime++;
        }
    }

    freePriorityQueue(pq);
}

void displayResults(Process processes[], int processCount) {
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    printf("\nPROCESS ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < processCount; i++) {
        printf("    %c\t\t     %d\t\t     %d\t\t   %d\t\t     %d\t\t     %d\t\t    %d\n", 
               processes[i].processID, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               processes[i].priority,
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

void freePriorityQueue(PriorityQueue *pq) {
    free(pq->heap);
    free(pq);
}

// Priority Queue Functions
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->heap = (Process *)malloc(sizeof(Process) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void insertProcess(PriorityQueue *pq, Process p) {
    pq->heap[pq->size] = p;
    int i = pq->size;
    pq->size++;

    while (i != 0 && pq->heap[i].priority < pq->heap[(i - 1) / 2].priority) {
        Process temp = pq->heap[i];
        pq->heap[i] = pq->heap[(i - 1) / 2];
        pq->heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Process extractHighestPriority(PriorityQueue *pq) {
    if (pq->size == 0) {
        Process empty = {0};
        return empty;
    }

    Process root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    minHeapify(pq, 0);
    return root;
}

bool isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

void minHeapify(PriorityQueue *pq, int idx) {
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int smallest = idx;

    if (left < pq->size && pq->heap[left].priority < pq->heap[smallest].priority) {
        smallest = left;
    }
    if (right < pq->size && pq->heap[right].priority < pq->heap[smallest].priority) {
        smallest = right;
    }
    if (smallest != idx) {
        Process temp = pq->heap[idx];
        pq->heap[idx] = pq->heap[smallest];
        pq->heap[smallest] = temp;
        minHeapify(pq, smallest);
    }
}
