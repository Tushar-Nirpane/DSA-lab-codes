#include <stdio.h>

#define MAX 100

typedef struct {
    int patientID;
    int arrivalTime;
} Patient;

typedef struct {
    Patient items[MAX];
    int front, rear, count;
} Queue;

void initQueue(Queue *q) { q->front = 0; q->rear = -1; q->count = 0; }

int isQueueEmpty(const Queue *q) { return q->count == 0; }
int isQueueFull(const Queue *q)  { return q->count == MAX; }

void addPatient(Queue *q, int id, int arrival) {
    if (isQueueFull(q)) { printf("Queue is full.\n"); return; }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear].patientID = id;
    q->items[q->rear].arrivalTime = arrival;
    q->count++;
    printf("Patient %d added.\n", id);
}

void attendPatient(Queue *q) {
    if (isQueueEmpty(q)) { printf("No patients waiting.\n"); return; }
    Patient p = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    printf("Attending patient %d (arrived at %d).\n", p.patientID, p.arrivalTime);
}

void viewPatients(const Queue *q) {
    if (isQueueEmpty(q)) { printf("No patients waiting.\n"); return; }
    printf("%-5s %-12s %-12s\n", "Pos", "Patient ID", "Arrival");
    for (int i = 0, idx = q->front; i < q->count; i++, idx = (idx + 1) % MAX)
        printf("%-5d %-12d %-12d\n", i + 1, q->items[idx].patientID,
               q->items[idx].arrivalTime);
}

int main(void) {
    Queue q;
    int choice, id, arrival;
    initQueue(&q);

    do {
        printf("\n1.Add patient 2.Attend patient 3.View waiting 4.Is queue empty "
               "0.Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:
            printf("Enter patient ID and arrival time: ");
            scanf("%d %d", &id, &arrival);
            addPatient(&q, id, arrival);
            break;
        case 2: attendPatient(&q); break;
        case 3: viewPatients(&q); break;
        case 4:
            printf(isQueueEmpty(&q) ? "Queue is empty.\n" : "Queue is not empty.\n");
            break;
        case 0: break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}
