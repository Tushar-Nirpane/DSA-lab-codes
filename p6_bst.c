
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int roll;
    struct Node *left;
    struct Node *right;

} Node; 
Node *createNode(int roll)
{
    Node *n = (Node *)malloc(sizeof(Node));

    if (n == NULL)
    {
        printf("Memory error.\n");
        exit(1);
    }

    n->roll = roll;
    n->left = NULL;
    n->right = NULL;

    return n;
}


Node *insert(Node *root, int roll)
{
    if (root == NULL)
    {
        return createNode(roll);
    }

    if (roll < root->roll)
    {
        root->left = insert(root->left, roll);
    }
    else if (roll > root->roll)
    {
        root->right = insert(root->right, roll);
    }
    else
    {
        printf("Roll %d already exists.\n", roll);
    }

    return root;
}


Node *minNode(Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }

    return root;
}


Node *removeRoll(Node *root, int roll, int *found)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (roll < root->roll)
    {
        root->left = removeRoll(root->left, roll, found);
    }
    else if (roll > root->roll)
    {
        root->right = removeRoll(root->right, roll, found);
    }
    else
    {
        *found = 1;

        if (root->left == NULL)
        {
            Node *r = root->right;

            free(root);

            return r;
        }

        if (root->right == NULL)
        {
            Node *l = root->left;

            free(root);

            return l;
        }

        Node *succ = minNode(root->right);

        root->roll = succ->roll;

        root->right = removeRoll(root->right, succ->roll, found);
    }

    return root;
}


Node *search(Node *root, int roll)
{
    while (root != NULL && root->roll != roll)
    {
        if (roll < root->roll)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return root;
}


void inorder(const Node *r)
{
    if (r != NULL)
    {
        inorder(r->left);

        printf("%d ", r->roll);

        inorder(r->right);
    }
}


void preorder(const Node *r)
{
    if (r != NULL)
    {
        printf("%d ", r->roll);

        preorder(r->left);

        preorder(r->right);
    }
}


void postorder(const Node *r)
{
    if (r != NULL)
    {
        postorder(r->left);

        postorder(r->right);

        printf("%d ", r->roll);
    }
}


void freeTree(Node *r)
{
    if (r != NULL)
    {
        freeTree(r->left);

        freeTree(r->right);

        free(r);
    }
}


// Main function
int main()
{
    Node *root = NULL;

    int choice;
    int roll;
    int found;

    do
    {
        printf("\n===== STUDENT BST MANAGEMENT =====\n");

        printf("1. Insert Roll Number\n");
        printf("2. Delete Roll Number\n");
        printf("3. Search Roll Number\n");
        printf("4. Display Traversals\n");
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
                printf("Enter roll number: ");

                scanf("%d", &roll);

                root = insert(root, roll);

                break;
            }

            case 2:
            {
                printf("Enter roll number to delete: ");

                scanf("%d", &roll);

                found = 0;

                root = removeRoll(root, roll, &found);

                if (found)
                {
                    printf("Deleted successfully.\n");
                }
                else
                {
                    printf("Roll not found.\n");
                }

                break;
            }

            case 3:
            {
                printf("Enter roll number to search: ");

                scanf("%d", &roll);

                if (search(root, roll) != NULL)
                {
                    printf("Student found.\n");
                }
                else
                {
                    printf("Student not found.\n");
                }

                break;
            }

            case 4:
            {
                printf("Inorder: ");

                inorder(root);

                printf("\n");

                printf("Preorder: ");

                preorder(root);

                printf("\n");

                printf("Postorder: ");

                postorder(root);

                printf("\n");

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

    freeTree(root);

    return 0;
}
