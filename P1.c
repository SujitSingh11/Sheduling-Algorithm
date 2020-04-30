#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

struct Node
{
    int processID;
    int arrival_time;
    int burst_time;
    struct Node *next;
};

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
        printf("Arrival time : %d \n", n->arrival_time);
        n = n->next;
    }
}

int getPID()
{
    static int pid = 1;
    return pid++;
}

void append(struct Node **head_ref, struct Node *n, int arrive, int burst)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *last = *head_ref;
    new_node->processID = getPID();
    new_node->arrival_time = arrive;
    new_node->burst_time = burst;
    new_node->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        printf("New process created\nProcessID: %d\nArrival Time: %d\nburst Time: %d\n\n", new_node->processID, new_node->arrival_time, new_node->burst_time);
        return;
    }
    printf("New process created\nProcessID: %d\nArrival Time: %d\nburst Time: %d\n\n", new_node->processID, new_node->arrival_time, new_node->burst_time);
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}

int main()
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
    int lower = 1, upper = 5, count = 1;
    int number, arrival_time, delay, burst_time;
    int number_of_process = 0;
    srand(time(0));

    while (number_of_process < 10)
    {
        delay = randoms(lower, 20, count);
        burst_time = randoms(lower, upper, count);
        arrival_time = delay;
        //sleep((int)delay);
        append(&head, head, arrival_time, burst_time);
        number_of_process++;
    }

    // Print Ready list
    printf("\nReady List: \n");
    printList(head);
    return 0;
}
