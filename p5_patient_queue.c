#include <stdio.h>

#define MAX 100

typedef struct
{
    int patientID;
    int arrivalTime;

} Patient;


typedef struct
{
    Patient items[MAX];
    int front;
    int rear;
    int count;

} Queue;


// 
void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}


int isQueueEmpty(const Queue *q)
{
    return q->count == 0;
}


int isQueueFull(const Queue *q)
{
    return q->count == MAX;
}


int isValidTime(int t)
{
    return t >= 0 && t / 100 < 24 && t % 100 < 60;
}


void printTime(int t)
{
    printf("%02d:%02d", t / 100, t % 100);
}


void addPatient(Queue *q, int id, int arrival)
{
    if (isQueueFull(q))
    {
        printf("Queue is full.\n");
        return;
    }

    q->rear = (q->rear + 1) % MAX;

    q->items[q->rear].patientID = id;
    q->items[q->rear].arrivalTime = arrival;

    q->count++;

    printf("Patient %d added (arrived at ", id);

    printTime(arrival);

    printf(").\n");
}


void attendPatient(Queue *q)
{
    if (isQueueEmpty(q))
    {
        printf("No patients waiting.\n");
        return;
    }

    Patient p = q->items[q->front];

    q->front = (q->front + 1) % MAX;

    q->count--;

    printf("Attending patient %d (arrived at ", p.patientID);

    printTime(p.arrivalTime);

    printf(").\n");
}


void viewPatients(const Queue *q)
{
    if (isQueueEmpty(q))
    {
        printf("No patients waiting.\n");
        return;
    }

    printf("%-5s %-12s %-8s\n", "Pos", "Patient ID", "Arrival");

    for (int i = 0, idx = q->front; i < q->count; i++, idx = (idx + 1) % MAX)
    {
        printf("%-5d %-12d ", i + 1, q->items[idx].patientID);

        printTime(q->items[idx].arrivalTime);

        printf("\n");
    }
}


int main()
{
    Queue q;

    int choice;
    int id;
    int arrival;

    initQueue(&q);

    do
    {
        printf("\n===== PATIENT QUEUE MANAGEMENT =====\n");

        printf("1. Add Patient\n");
        printf("2. Attend Patient\n");
        printf("3. View Waiting Patients\n");
        printf("4. Check if Queue is Empty\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            break;
        }

        switch (choice)
        {
            case 1:
            {
                printf("Enter patient ID: ");

                if (scanf("%d", &id) != 1)
                {
                    return 0;
                }

                printf("Enter arrival time (HHMM, e.g. 930 = 09:30): ");

                if (scanf("%d", &arrival) != 1)
                {
                    return 0;
                }

                if (!isValidTime(arrival))
                {
                    printf("Invalid time. Use HHMM between 0000 and 2359.\n");
                    break;
                }

                addPatient(&q, id, arrival);

                break;
            }

            case 2:
            {
                attendPatient(&q);
                break;
            }

            case 3:
            {
                viewPatients(&q);
                break;
            }

            case 4:
            {
                printf("%s\n", isQueueEmpty(&q) ? "Queue is empty." : "Queue is not empty.");
                break;
            }

            case 0:
            {
                printf("Exiting program. Thank you!\n");
                break;
            }

            default:
            {
                printf("Invalid choice. Please try again.\n");
            }
        }

    } while (choice != 0);

    return 0;
}
