#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

struct Node
{
    int processID;
    int arrival_time;
    int burst_time;
    int complete_time;
    int wait_time;
    int turn_around_time;
    int priority;
    int service_time;
    struct Node *next;
};

struct Node *start = NULL;

int randoms(int lower, int upper, int count)
{
    int i, num;
    for (i = 0; i < count; i++)
    {
        num = (rand() % (upper - lower + 1)) + lower;
    }
    return num;
}

void printList(struct Node *n)
{
    while (n != NULL)
    {
        printf("ProcessID : %d \t burst Time : %d \t", n->processID, n->burst_time);
        printf("Arrival time : %d \t", n->arrival_time);
        printf("Priority : %d \n", n->priority);

        n = n->next;
    }
}

int getPID()
{
    static int pid = 1;
    return pid++;
}

void append(struct Node **head_ref, struct Node *n, int arrive, int burst, int priority)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *last = *head_ref;
    new_node->processID = getPID();
    new_node->arrival_time = arrive;
    new_node->burst_time = burst;
    new_node->priority = priority;
    new_node->next = NULL;
    if (start == NULL)
    {
        start = new_node;
    }
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        printf("New process created\nProcessID: %d\nArrival Time: %d\nBurst Time: %d\nPriority: %d\n\n", new_node->processID, new_node->arrival_time, new_node->burst_time, new_node->priority);
        return;
    }
    printf("New process created\nProcessID: %d\nArrival Time: %d\nburst Time: %d\npriority: %d\n\n", new_node->processID, new_node->arrival_time, new_node->burst_time, new_node->priority);
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}

void printResult(struct Node *n)
{
    printf("\n\nProcessID\tBurst Time\tArrival Time\tComplete Time\tWait Time\tTurnaround Time\n");
    while (n != NULL)
    {
        printf("   %d\t\t    %d\t\t    %d\t\t    %d\t\t    %d\t\t       %d\n", n->processID, n->burst_time, n->arrival_time, n->complete_time, n->wait_time, n->turn_around_time);
        n = n->next;
    }
}
void wait_time(struct Node *n)
{
    int service, burst;
    n = start;
    n->wait_time = 0;
    n->service_time = 0;
    service = n->service_time;
    burst = n->burst_time;
    n = n->next;
    while (n != NULL)
    {
        n->service_time = service + burst;
        service = n->service_time;
        burst = n->burst_time;
        n->wait_time = n->service_time - n->arrival_time; // Waiting time of process
        if (n->wait_time < 0)
        {
            n->wait_time = 0;
        }
        n = n->next;
    }
}

void turn_around_time(struct Node *n)
{
    n = start;
    int c = n->arrival_time;
    while (n != NULL)
    {
        c = c + n->arrival_time;
        n->complete_time = c + n->burst_time; // Completion time of process
        c = n->complete_time;
        n->turn_around_time = n->burst_time + n->wait_time; // Turnaround time of process
        n = n->next;
    }
}

void fcfs(struct Node *n)
{
    struct Node *next_node;
    int temp;

    // Sorting the linked list in ascending order of Arrival times using bubble sort
    n = start;
    while (n != NULL)
    {
        next_node = n->next;
        while (next_node != NULL)
        {
            if (n->arrival_time > next_node->arrival_time)
            {
                temp = n->processID;
                n->processID = next_node->processID;
                next_node->processID = temp;

                temp = n->arrival_time;
                n->arrival_time = next_node->arrival_time;
                next_node->arrival_time = temp;

                temp = n->burst_time;
                n->burst_time = next_node->burst_time;
                next_node->burst_time = temp;

                temp = n->complete_time;
                n->complete_time = next_node->complete_time;
                next_node->complete_time = temp;

                temp = n->wait_time;
                n->wait_time = next_node->wait_time;
                next_node->wait_time = temp;

                temp = n->turn_around_time;
                n->turn_around_time = next_node->turn_around_time;
                next_node->turn_around_time = temp;

                temp = n->priority;
                n->priority = next_node->priority;
                next_node->priority = temp;
            }
            next_node = next_node->next;
        }
        n = n->next;
    }

    // Displaying the gantt  chart
    n = start;
    printf("\n\nMaking a Read Queue for FCFS.............. \n");
    printf("\n\nRead Queue: \n");
    printList(n);
    printf("\n\n-----------------Gantt  Chart-------------------\n\n");

    while (n != NULL)
    {
        printf("P[%d]\t", n->processID);
        n = n->next;
    }
    // Wait Time Calculation
    wait_time(n);

    // Turn Around Time Calculation
    turn_around_time(n);

    // Average Wait and Turn Around Time
    float total_wait = 0, total_tat = 0;
    int total_process = 0;
    n = start;
    while (n != NULL)
    {
        total_wait = total_wait + n->wait_time;
        total_tat = total_tat + n->turn_around_time;
        total_process++;
        n = n->next;
    }

    // Printing the Result
    printf("\n\n------------------------------------Final Table of Processes------------------------------------");
    n = start;
    printResult(n);
    printf("\nAverage Wait Time: %f\nAverage Turnaround Time: %f", (float)(total_wait / total_process), (float)(total_tat / total_process));
    return;
}

void sjfs(struct Node *n)
{
    struct Node *next_node;
    int temp;

    // Sorting the linked list in ascending order of Burst times using bubble sort
    n = start;
    while (n != NULL)
    {
        next_node = n->next;
        while (next_node != NULL)
        {
            if (n->burst_time > next_node->burst_time)
            {
                temp = n->processID;
                n->processID = next_node->processID;
                next_node->processID = temp;

                temp = n->arrival_time;
                n->arrival_time = next_node->arrival_time;
                next_node->arrival_time = temp;

                temp = n->burst_time;
                n->burst_time = next_node->burst_time;
                next_node->burst_time = temp;

                temp = n->complete_time;
                n->complete_time = next_node->complete_time;
                next_node->complete_time = temp;

                temp = n->wait_time;
                n->wait_time = next_node->wait_time;
                next_node->wait_time = temp;

                temp = n->turn_around_time;
                n->turn_around_time = next_node->turn_around_time;
                next_node->turn_around_time = temp;

                temp = n->priority;
                n->priority = next_node->priority;
                next_node->priority = temp;
            }
            next_node = next_node->next;
        }
        n = n->next;
    }

    // Displaying the gantt  chart
    n = start;
    printf("\n\nMaking a Read Queue for SJFS.............. \n");
    printf("\n\nRead Queue: \n");
    printList(n);
    printf("\n\n-----------------Gantt  Chart-------------------\n\n");

    while (n != NULL)
    {
        printf("P[%d]\t", n->processID);
        n = n->next;
    }
    // Wait Time Calculation
    wait_time(n);

    // Turn Around Time Calculation
    turn_around_time(n);

    // Average Wait and Turn Around Time
    float total_wait = 0, total_tat = 0;
    int total_process = 0;
    n = start;
    while (n != NULL)
    {
        total_wait = total_wait + n->wait_time;
        total_tat = total_tat + n->turn_around_time;
        total_process++;
        n = n->next;
    }

    // Printing the Result
    printf("\n\n------------------------------------Final Table of Processes------------------------------------");
    n = start;
    printResult(n);
    printf("\nAverage Wait Time: %f\nAverage Turnaround Time: %f", (float)(total_wait / total_process), (float)(total_tat / total_process));
    return;
}

void priority_scheduling(struct Node *n)
{
    struct Node *next_node;
    int temp;

    // Sorting the linked list in ascending order of Burst times using bubble sort
    n = start;
    while (n != NULL)
    {
        next_node = n->next;
        while (next_node != NULL)
        {
            if (n->priority > next_node->priority)
            {
                temp = n->processID;
                n->processID = next_node->processID;
                next_node->processID = temp;

                temp = n->arrival_time;
                n->arrival_time = next_node->arrival_time;
                next_node->arrival_time = temp;

                temp = n->burst_time;
                n->burst_time = next_node->burst_time;
                next_node->burst_time = temp;

                temp = n->complete_time;
                n->complete_time = next_node->complete_time;
                next_node->complete_time = temp;

                temp = n->wait_time;
                n->wait_time = next_node->wait_time;
                next_node->wait_time = temp;

                temp = n->turn_around_time;
                n->turn_around_time = next_node->turn_around_time;
                next_node->turn_around_time = temp;

                temp = n->priority;
                n->priority = next_node->priority;
                next_node->priority = temp;
            }
            next_node = next_node->next;
        }
        n = n->next;
    }

    // Displaying the gantt  chart
    n = start;
    printf("\n\nMaking a Read Queue for Priority Scheduling.............. \n");
    printf("\n\nRead Queue: \n");
    printList(n);
    printf("\n\n-----------------Gantt  Chart-------------------\n\n");

    while (n != NULL)
    {
        printf("P[%d]\t", n->processID);
        n = n->next;
    }
    // Wait Time Calculation
    wait_time(n);

    // Turn Around Time Calculation
    turn_around_time(n);

    // Average Wait and Turn Around Time
    float total_wait = 0, total_tat = 0;
    int total_process = 0;
    n = start;
    while (n != NULL)
    {
        total_wait = total_wait + n->wait_time;
        total_tat = total_tat + n->turn_around_time;
        total_process++;
        n = n->next;
    }

    // Printing the Result
    printf("\n\n------------------------------------Final Table of Processes------------------------------------");
    n = start;
    printResult(n);
    printf("\nAverage Wait Time: %f\nAverage Turnaround Time: %f", (float)(total_wait / total_process), (float)(total_tat / total_process));
    return;
}

int main()
{
    struct Node *head = NULL;
    int lower = 1, upper = 10, count = 1;
    int number, arrival_time, delay, burst_time, priority;
    int number_of_process = 0;
    srand(time(0));

    while (number_of_process < 10)
    {
        delay = randoms(0, 20, count);
        burst_time = randoms(lower, upper, count);
        arrival_time = delay;
        priority = randoms(lower, 10, count);
        //sleep((int)delay);
        append(&head, head, arrival_time, burst_time, priority);
        number_of_process++;
    }

    // Print Ready list
    printf("\nReady List: \n");
    printList(head);

    // FCFS Scheduling
    fcfs(head);

    // SJFS Scheduling
    sjfs(head);

    // Priority Scheduling
    priority_scheduling(head);

    return 0;
}
