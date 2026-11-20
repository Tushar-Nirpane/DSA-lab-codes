#include <stdio.h>

#define MAX 100

void display(const int a[], int n) {
    if (n == 0) { printf("Array is empty.\n"); return; }
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int insertMark(int a[], int *n, int mark) {
    if (*n >= MAX) return 0;
    a[(*n)++] = mark;
    return 1;
}

int deleteAt(int a[], int *n, int pos) {
    if (pos < 1 || pos > *n) return 0;
    for (int i = pos - 1; i < *n - 1; i++)
        a[i] = a[i + 1];
    (*n)--;
    return 1;
}

int linearSearch(const int a[], int n, int key) {
    for (int i = 0; i < n; i++)
        if (a[i] == key) return i;
    return -1;
}

void sortArray(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
            }
}

int binarySearch(const int a[], int n, int key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == key) return mid;
        if (a[mid] < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main(void) {
    int marks[MAX], n = 0, choice, value, pos;

    do {
        printf("\n1.Insert 2.Delete at position 3.Display 4.Linear search "
               "5.Sort + Binary search 0.Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:
            printf("Enter mark: ");
            scanf("%d", &value);
            if (insertMark(marks, &n, value)) printf("Inserted.\n");
            else printf("Array full.\n");
            break;
        case 2:
            printf("Enter position (1-%d): ", n);
            scanf("%d", &pos);
            if (deleteAt(marks, &n, pos)) printf("Deleted.\n");
            else printf("Invalid position.\n");
            break;
        case 3:
            display(marks, n);
            break;
        case 4:
            printf("Enter mark to search: ");
            scanf("%d", &value);
            pos = linearSearch(marks, n, value);
            if (pos >= 0) printf("Found at position %d.\n", pos + 1);
            else printf("Not found.\n");
            break;
        case 5:
            sortArray(marks, n);
            printf("Sorted: "); display(marks, n);
            printf("Enter mark to search (binary): ");
            scanf("%d", &value);
            pos = binarySearch(marks, n, value);
            if (pos >= 0) printf("Found at position %d.\n", pos + 1);
            else printf("Not found.\n");
            break;
        case 0:
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}
