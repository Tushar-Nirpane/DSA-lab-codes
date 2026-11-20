#include <stdio.h>

#define MAX 100

void display(const int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void bubbleSort(int arr[], int n) {
    for (int pass = 0; pass < n - 1; pass++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - pass; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        printf("After pass %d: ", pass + 1);
        display(arr, n);
        if (!swapped)
            break;
    }
}

int main(void) {
    int roll[MAX];
    int n;

    printf("Enter number of students (max %d): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of students.\n");
        return 1;
    }

    printf("Enter %d roll numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Roll %d: ", i + 1);
        if (scanf("%d", &roll[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    printf("\nOriginal roll numbers: ");
    display(roll, n);

    printf("\nSorting passes:\n");
    bubbleSort(roll, n);

    printf("\nSorted roll numbers (ascending): ");
    display(roll, n);

    return 0;
}
