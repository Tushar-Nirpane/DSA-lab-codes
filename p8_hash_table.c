#include <stdio.h>

#define TABLE_SIZE 11
#define EMPTY  -1

int table[TABLE_SIZE];

void initTable(void) {
    for (int i = 0; i < TABLE_SIZE; i++) table[i] = EMPTY;
}

int hash(int key) { return key % TABLE_SIZE; }

int insertBook(int id) {
    int idx = hash(id);
    for (int probes = 0; probes < TABLE_SIZE; probes++) {
        int pos = (idx + probes) % TABLE_SIZE;
        if (table[pos] == EMPTY) {
            table[pos] = id;
            printf("Book %d stored at index %d (probes: %d)\n", id, pos, probes + 1);
            return 1;
        }
        if (table[pos] == id) {
            printf("Book %d already exists.\n", id);
            return 0;
        }
    }
    printf("Index is full, cannot insert book %d.\n", id);
    return 0;
}

int searchBook(int id) {
    int idx = hash(id);
    for (int probes = 0; probes < TABLE_SIZE; probes++) {
        int pos = (idx + probes) % TABLE_SIZE;
        if (table[pos] == EMPTY) break;
        if (table[pos] == id) return pos;
    }
    return -1;
}

void display(void) {
    printf("Index  Book ID\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] == EMPTY) printf("%-6d -\n", i);
        else                   printf("%-6d %d\n", i, table[i]);
    }
}

int main(void) {
    int choice, id, pos;
    initTable();

    do {
        printf("\n1.Insert book ID 2.Search book ID 3.Display index 0.Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:
            printf("Enter book ID: ");
            scanf("%d", &id);
            insertBook(id);
            break;
        case 2:
            printf("Enter book ID to search: ");
            scanf("%d", &id);
            pos = searchBook(id);
            if (pos >= 0) printf("Book %d found at index %d.\n", id, pos);
            else printf("Book %d not found.\n", id);
            break;
        case 3:
            display();
            break;
        case 0: break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}
