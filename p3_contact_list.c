
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define PHONE_LEN 20
typedef struct Contact
{
    char name[NAME_LEN];
    char phone[PHONE_LEN];

    struct Contact *next;

} Contact;

Contact *createContact(const char *name, const char *phone)
{
    Contact *node = (Contact *)malloc(sizeof(Contact));

    if (node == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    strncpy(node->name, name, NAME_LEN - 1);
    node->name[NAME_LEN - 1] = '\0';

    strncpy(node->phone, phone, PHONE_LEN - 1);
    node->phone[PHONE_LEN - 1] = '\0';

    node->next = NULL;

    return node;
}

Contact *insertAtBeginning(Contact *head, const char *name, const char *phone)
{
    Contact *node = createContact(name, phone);

    if (node == NULL)
    {
        return head;
    }

    node->next = head;

    printf("Contact '%s' added at beginning.\n", name);

    return node;
}

Contact *insertAtEnd(Contact *head, const char *name, const char *phone)
{
    Contact *node = createContact(name, phone);

    if (node == NULL)
    {
        return head;
    }

    if (head == NULL)
    {
        printf("Contact '%s' added (list was empty).\n", name);
        return node;
    }

    Contact *cur = head;

    while (cur->next != NULL)
    {
        cur = cur->next;
    }

    cur->next = node;

    printf("Contact '%s' added at end.\n", name);

    return head;
}

Contact *deleteByName(Contact *head, const char *name)
{
    Contact *cur = head;
    Contact *prev = NULL;

    while (cur != NULL && strcmp(cur->name, name) != 0)
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL)
    {
        printf("Contact '%s' not found.\n", name);
        return head;
    }

    if (prev == NULL)
    {
        head = cur->next;
    }
    else
    {
        prev->next = cur->next;
    }

    free(cur);

    printf("Contact '%s' deleted.\n", name);

    return head;
}

void searchContact(const Contact *head, const char *name)
{
    const Contact *cur = head;

    while (cur != NULL)
    {
        if (strcmp(cur->name, name) == 0)
        {
            printf("Found: %s - %s\n", cur->name, cur->phone);
            return;
        }

        cur = cur->next;
    }

    printf("Contact '%s' not found.\n", name);
}

void displayContacts(const Contact *head)
{
    if (head == NULL)
    {
        printf("Contact list is empty.\n");
        return;
    }

    int count = 1;

    printf("\n%-5s %-25s %-15s\n", "No.", "Name", "Phone");
    printf("---------------------------------------------------\n");

    for (const Contact *cur = head; cur != NULL; cur = cur->next)
    {
        printf("%-5d %-25s %-15s\n", count, cur->name, cur->phone);
        count++;
    }
}

void freeList(Contact *head)
{
    while (head != NULL)
    {
        Contact *temp = head;
        head = head->next;

        free(temp);
    }
}

void readLine(char *buf, int size)
{
    if (fgets(buf, size, stdin) != NULL)
    {
        buf[strcspn(buf, "\n")] = '\0';
    }
}

int main()
{
    Contact *head = NULL;

    int choice;

    char name[NAME_LEN];
    char phone[PHONE_LEN];

    do
    {
        printf("\n===== CONTACT LIST MENU =====\n");

        printf("1. Insert contact at beginning\n");
        printf("2. Insert contact at end\n");
        printf("3. Delete contact by name\n");
        printf("4. Search contact by name\n");
        printf("5. Display all contacts\n");
        printf("0. Exit\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            break;
        }

        getchar();

        switch (choice)
        {
            case 1:
            {
                printf("Enter name: ");
                readLine(name, NAME_LEN);

                printf("Enter phone: ");
                readLine(phone, PHONE_LEN);

                head = insertAtBeginning(head, name, phone);

                break;
            }

            case 2:
            {
                printf("Enter name: ");
                readLine(name, NAME_LEN);

                printf("Enter phone: ");
                readLine(phone, PHONE_LEN);

                head = insertAtEnd(head, name, phone);

                break;
            }

            case 3:
            {
                printf("Enter name to delete: ");
                readLine(name, NAME_LEN);

                head = deleteByName(head, name);

                break;
            }

            case 4:
            {
                printf("Enter name to search: ");
                readLine(name, NAME_LEN);

                searchContact(head, name);

                break;
            }

            case 5:
            {
                displayContacts(head);

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

    freeList(head);

    return 0;
}
