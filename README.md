# Operating Systems: Algorithms and Programs

[Canva Link of Gantt Charts and Calculations](https://www.canva.com/design/DAGX-djUifE/j6fBPbmWF-SQ_KMRbTBLBA/edit?utm_content=DAGX-djUifE&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)

---

## CPU Scheduling in Operating Systems: Definition

CPU scheduling is the process of determining which process in the ready queue will be allocated to the CPU for execution next. It is a critical function of an operating system's process management component, aiming to optimize CPU utilization and ensure that system resources are used efficiently.

### **Key Concepts**

- **Ready Queue**: A list of processes that are ready to execute and waiting for CPU allocation.
- **Dispatcher**: A module that switches the CPU to the process selected by the scheduler.

---

### Preemptive Scheduling
Allows the operating system to interrupt and switch out the current running process if a higher-priority process arrives.

**Examples:**
- Round Robin (RR)
- Shortest Remaining Time First (SRTF)
- Priority Scheduling (preemptive)

---

### Non-Preemptive Scheduling
Once a process is allocated the CPU, it cannot be preempted until it finishes its burst time.

**Examples:**
- First-Come, First-Served (FCFS)
- Shortest Job Next (SJN)
- Priority Scheduling (non-preemptive)

---

### Key Terms
- **Process Arrival Times**: Determines the order processes are available.
- **Burst Time**: The time required for process execution.
- **Priorities**: Determines the urgency of processes.
- **Time Quantum**: For Round Robin scheduling, affects responsiveness.

---

## CPU Scheduling Algorithms

### **1. First Come, First Served (FCFS) Non-Preemptive**
- **Description**: Simplest CPU scheduling algorithm that schedules according to arrival times of processes. Implemented by using the FIFO queue.
- **Data Structure**: Queue of Processes by Arrival Time.
- **Code Description**: Processes are placed in the ready-queue-min-heap with the order of having the process that arrived first at the very top. To simulate the execution of these processes, the process is removed from the heap and enqueued into the queue.

---

### **2. Shortest Job First (SJF)**
- **Type**: Non-preemptive.
- **Description**: Selects the process with the shortest burst time for execution next, minimizing the average waiting and turnaround times.
- **Data Structure**: Min-Heap Based on Burst Time.
- **Code Description**: The process is selected by iterating over the list of processes, tracking the current time. Among processes with the same burst time, the one that arrives first is executed first.

---

### **3. Priority-Based Non-Preemptive Scheduling**
- **Description**: Processes are scheduled in order of priority value, and the CPU is allocated to the process with the highest priority.
- **Data Structure**: Heap Based on Priority Value.
- **Code Description**: Processes are executed in order of their priority. The lowest numerical value indicates higher priority.

---

### **4. Priority-Based Preemptive Scheduling**
- **Description**: CPU is preempted and switched to a higher-priority process as it arrives.
- **Data Structure**: Heap for Dynamic Priority Management
- **Pseudocode**: Maintain a ready queue with all processes and their priorities. The CPU scheduler checks the queue and selects the process with the highest priority. If a higher-priority process arrives, preempt the running process and place it back in the ready queue.

---

### **5. Round Robin Scheduling**
- **Type**: Preemptive.
- **Description**: Allocates a fixed time quantum to each process in the ready queue in a circular order. If the process doesn't finish during the allocated quantum, it is preempted and moved to the back of the queue.
- **Data Structure**: Circular Queue for Processes.
- **Pseudocode**: All processes are added to a circular queue in their order of arrival. The scheduler picks the process at the front of the queue and allows it to execute for one time quantum. If the process completes during its quantum, remove it from the queue. If not, preempt it and place it at the end of the queue.

---

### **6. Shortest Remaining Time First**
- **Type**: Preemptive.
- **Description**: This is the preemptive version of SJF. The process with the least remaining burst time is scheduled for execution next.
- **Data Structure**: Min-Heap of Remaining Burst Times.

---

## Page Replacement Algorithms

### **1. First In First Out (FIFO)**
- **Description**: Oldest page is removed when a new page needs to be loaded into memory.
- **Implementation**: OS keeps track of all pages in memory in a queue.

---

### **2. Least Recently Used (LRU)**
- **Description**: The page that is least recently used will be replaced.

---

### **3. Optimal Replacement**
- **Description**: This algorithm always replaces the page that won't be needed for the longest time.

---

## IO Management Algorithms

### **1. First Come, First Serve (FCFS)**
- **Description**: One of the simplest, easy to program, and essentially fair. However, it suffers from high seek time.

---

### **2. C Scan Scheduling Algorithm**

---

### **3. C Look Scheduling Algorithm**

---

### End of Document
