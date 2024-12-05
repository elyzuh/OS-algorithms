/****************************************************************************************
*   Name:           Katrina Elyza Ventura & Fabiola Villanueva                          *
*   Description:    First Come, First Serve - CPU Scheduling Algorithm                  *
*                   Minheap Set of Given Processes then Enqueue to be Executed          *
*   Date:           11 / 08 / 24                                                        *
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 0XF

typedef struct {
    char id;
    int arrvalT;
    int burstT;
    int completionT;
    int turnaroundT;
    int waitingT;
} processType;

typedef struct node {
    processType data;
    struct node *link;
} NodeType, *NODE;

typedef struct {
    processType minHeap[SIZE];
    int lastIdx;
} heapType;                                                                                                             // waiting minHeap to executed queue in linked list

typedef struct {
    NODE front;
    NODE rear;
    float avgTurnTime;
    float avgWaitTime;
} execQueueList;

void waitingProcesses (heapType *H, processType elem);
void displayWaiting (heapType H);
void enqueueProcess (heapType *H, execQueueList *QLL);                                                                  // queue data structure represented in linked list
void displayExecQueue (execQueueList QLL);
void executingProcesses (execQueueList *QLL);

void main () {
    system("CLS");
    printf("START\n");

    heapType myHeap = {.lastIdx = -1};
    execQueueList myQueue = {NULL, NULL, 0, 0};
    int x;

    processType arr[5] = {                                                                                              // sample static data
        {'A', 0, 10, 0, 0, 0},
        {'B', 2,  5, 0, 0, 0},
        {'C', 3,  2, 0, 0, 0},
        {'D', 5, 20, 0, 0, 0},
        {'E', 8, 10, 0, 0, 0}
    };

    for ( x = 0; x < 5; ++x) {
        waitingProcesses (&myHeap, arr[x]);
    }
    displayWaiting (myHeap);

    enqueueProcess (&myHeap, &myQueue);
    // displayExecQueue (myQueue);

    executingProcesses (&myQueue);

    printf("\n\nEND");
}

void waitingProcesses (heapType *H, processType elem) {                                                                 // heap by priority of arrival time
    printf("\n...inserting Process %c", elem.id);
    if (H->lastIdx < SIZE-1) {
        int x;                                                                                                          // heapifying by shifting method
        for (x = ++(H->lastIdx); x > 0 && elem.arrvalT < H->minHeap[(x - 1) / 2].arrvalT; x = (x - 1) / 2) {
            H->minHeap[x] = H->minHeap[(x - 1) / 2];
        }
        H->minHeap[x] = elem;
    }
}

void displayWaiting (heapType H) {
    printf("\n\nPROCESS QUEUE ::");
    printf("\n ID    |   AT  |   BT  |   CT  |  TAT  |   WT");
    printf("\n----------------------------------------------");

    int x;
    for (x = 0; x <= H.lastIdx; ++x) {
        printf("\n %2c    |   %2d  |   %2d  |   %2d  |   %2d  |   %2d", 
            H.minHeap[x].id,
            H.minHeap[x].arrvalT,
            H.minHeap[x].burstT,
            H.minHeap[x].completionT,
            H.minHeap[x].turnaroundT,
            H.minHeap[x].waitingT
            );
    }
}

void enqueueProcess (heapType *H, execQueueList *QLL) {
    int currentTime = 0;                                                                                            // time always starts at zero

    while (H->lastIdx >= 0) {                                                                                       // if heap is not empty, then there is porcess to execute
        NODE newProcess = malloc (sizeof (NodeType));
        if (newProcess != NULL) {
            newProcess->data = H->minHeap[0];                                                                       // root of the heap is the data to enqueue
            newProcess->link = NULL;

            if (currentTime < newProcess->data.arrvalT) {                                                           // if the current time is less than the arrival time of current process,
                currentTime = newProcess->data.arrvalT;                                                             // then update the current time to jump to arrival time of process
            }
            currentTime += newProcess->data.burstT;                                                                 // increment the current time with burst time
            newProcess->data.completionT = currentTime;                                                             // new current time shall be the completion time of the process

            printf("\n...enqueueing process %c", newProcess->data.id);

            if (QLL->front != NULL) {                                                                               // enqueue the new process to be executed
                QLL->rear->link = newProcess;
            } else {
                QLL->front = newProcess;
            }
            QLL->rear = newProcess;

            H->minHeap[0] = H->minHeap[H->lastIdx--];                                                               // overwrite with a new root, then heapify by push down
            int a, b;
            for (a = 0; ((2 * a) + 1) <= H->lastIdx; a = b) {
                if (((2 * a) + 2) <= H->lastIdx && (H->minHeap[(2 * a) + 2].arrvalT < H->minHeap[(2 * a) + 1].arrvalT)) {
                    b = (2 * a) + 2;                                                                                // if two children, compare and get smaller index
                } else {
                    b = (2 * a) + 1;
                }

                if (a != b && H->minHeap[b].arrvalT < H->minHeap[a].arrvalT) {                                      // if the element to swap with is not itself, then push down the parent by swapping with the child
                    processType tempProc = H->minHeap[a];
                    H->minHeap[a] = H->minHeap[b];
                    H->minHeap[b] = tempProc;
                } else {
                    a = H->lastIdx;
                }
            }
        }
    }
}

void displayExecQueue (execQueueList QLL) {                                                                         // traversing the queue for display only IM SO SORRY
    printf("\n\nQUEUE OF PROCESSES W/O DEQUEUEING :: (TEST)");
    printf("\n ID    |   AT  |   BT  |   CT  |  TAT  |   WT");
    printf("\n----------------------------------------------");
    NODE trav;
    for (trav = QLL.front; trav != NULL; trav = trav->link) {
        printf("\n %2c    |   %2d  |   %2d  |   %2d  |   %2d  |   %2d", 
            trav->data.id,
            trav->data.arrvalT,
            trav->data.burstT,
            trav->data.completionT,
            trav->data.turnaroundT,
            trav->data.waitingT
        );
    }
}

void executingProcesses (execQueueList *QLL) {
    printf("\n\nEXECUTING PROCESSES W/ TIME FORMULAS :: (GANTT CHART HORIZONTAL)");
    printf("\n EX    |   AT  |   BT  |   CT  |  TAT  |   WT");
    printf("\n----------------------------------------------");
    int totalTAT = 0, totalWaitingT = 0, count = 0, TAT, WT;

    NODE tempDel;
    while (QLL->front != NULL) {
        tempDel = QLL->front;
        QLL->front = tempDel->link;

        // printf("\n...executing %c", tempDel->data.id);

        TAT = tempDel->data.completionT - tempDel->data.arrvalT;                                                    // grab TAT and WT before freeing the process
        WT = TAT - tempDel->data.burstT;
        tempDel->data.turnaroundT = TAT;                                                                            // assignment for display before free
        tempDel->data.waitingT = WT;

        totalTAT += TAT;
        totalWaitingT += WT;
        count++;

        printf("\n %2c    |   %2d  |   %2d  |   %2d  |   %2d  |   %2d", 
            tempDel->data.id,
            tempDel->data.arrvalT,
            tempDel->data.burstT,
            tempDel->data.completionT,
            tempDel->data.turnaroundT,
            tempDel->data.waitingT
        );

        free (tempDel);
    }
    QLL->rear = NULL;                                                                                               // declares the queue is now empty

    float avgTAT = (float) totalTAT / count;
    float avgWT = (float) totalWaitingT / count;
    printf("\nAverage Turnaround Time :: %2.2f", avgTAT);
    printf("\nAverage Waiting Time :: %2.2f", avgWT);
}