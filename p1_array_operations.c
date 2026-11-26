
#include <stdio.h>
#define MAX 100

void display(const int a[], int n)
{
    if (n == 0)
    {
        printf("Array is empty.\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");
}
int insertMark(int a[], int *n, int mark)
{
    if (*n >= MAX)
    {
        return 0;
    }

    a[*n] = mark;
    (*n)++;

    return 1;
}
int deleteAt(int a[], int *n, int pos)
{
    if (pos < 1 || pos > *n)
    {
        return 0;
    }

    for (int i = pos - 1; i < *n - 1; i++)
    {
        a[i] = a[i + 1];
    }

    (*n)--;

    return 1;
}

int linearSearch(const int a[], int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == key)
        {
            return i;
        }
    }

    return -1;
}

void sortArray(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int binarySearch(const int a[], int n, int key)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (a[mid] == key)
        {
            return mid;
        }

        if (a[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}
int main()
{
    int marks[MAX];
    int n = 0;
    int choice, value, pos;

    do
    {
        printf("\n===== MARKS MANAGEMENT SYSTEM =====\n");
        printf("1. Insert Mark\n");
        printf("2. Delete at Position\n");
        printf("3. Display Array\n");
        printf("4. Linear Search\n");
        printf("5. Sort and Binary Search\n");
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
                printf("Enter mark: ");
                scanf("%d", &value);

                if (insertMark(marks, &n, value))
                {
                    printf("Mark inserted successfully.\n");
                }
                else
                {
                    printf("Array is full.\n");
                }

                break;
            }

            case 2:
            {
                printf("Enter position (1-%d): ", n);
                scanf("%d", &pos);

                if (deleteAt(marks, &n, pos))
                {
                    printf("Element deleted successfully.\n");
                }
                else
                {
                    printf("Invalid position.\n");
                }

                break;
            }

            case 3:
            {
                printf("Array elements: ");
                display(marks, n);

                break;
            }

            case 4:
            {
                printf("Enter mark to search: ");
                scanf("%d", &value);

                pos = linearSearch(marks, n, value);

                if (pos >= 0)
                {
                    printf("Mark found at position %d.\n", pos + 1);
                }
                else
                {
                    printf("Mark not found.\n");
                }

                break;
            }

            case 5:
            {
                sortArray(marks, n);

                printf("Sorted array: ");
                display(marks, n);

                printf("Enter mark to search: ");
                scanf("%d", &value);

                pos = binarySearch(marks, n, value);

                if (pos >= 0)
                {
                    printf("Mark found at position %d.\n", pos + 1);
                }
                else
                {
                    printf("Mark not found.\n");
                }

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
