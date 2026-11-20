#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int roll;
    struct Node *left, *right;
} Node;

Node *createNode(int roll) {
    Node *n = malloc(sizeof(Node));
    if (!n) { printf("Memory error.\n"); exit(1); }
    n->roll = roll;
    n->left = n->right = NULL;
    return n;
}

Node *insert(Node *root, int roll) {
    if (root == NULL) return createNode(roll);
    if (roll < root->roll)      root->left  = insert(root->left, roll);
    else if (roll > root->roll) root->right = insert(root->right, roll);
    else printf("Roll %d already exists.\n", roll);
    return root;
}

Node *minNode(Node *root) {
    while (root->left != NULL) root = root->left;
    return root;
}

Node *removeRoll(Node *root, int roll, int *found) {
    if (root == NULL) return NULL;
    if (roll < root->roll) {
        root->left = removeRoll(root->left, roll, found);
    } else if (roll > root->roll) {
        root->right = removeRoll(root->right, roll, found);
    } else {
        *found = 1;
        if (root->left == NULL) {
            Node *r = root->right; free(root); return r;
        }
        if (root->right == NULL) {
            Node *l = root->left; free(root); return l;
        }
        Node *succ = minNode(root->right);
        root->roll = succ->roll;
        root->right = removeRoll(root->right, succ->roll, found);
    }
    return root;
}

Node *search(Node *root, int roll) {
    while (root != NULL && root->roll != roll)
        root = (roll < root->roll) ? root->left : root->right;
    return root;
}

void inorder(const Node *r)   { if (r) { inorder(r->left);  printf("%d ", r->roll); inorder(r->right); } }
void preorder(const Node *r)  { if (r) { printf("%d ", r->roll); preorder(r->left); preorder(r->right); } }
void postorder(const Node *r) { if (r) { postorder(r->left); postorder(r->right); printf("%d ", r->roll); } }

void freeTree(Node *r) { if (r) { freeTree(r->left); freeTree(r->right); free(r); } }

int main(void) {
    Node *root = NULL;
    int choice, roll, found;

    do {
        printf("\n1.Insert 2.Delete 3.Search 4.Traversals 0.Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:
            printf("Enter roll number: ");
            scanf("%d", &roll);
            root = insert(root, roll);
            break;
        case 2:
            printf("Enter roll number to delete: ");
            scanf("%d", &roll);
            found = 0;
            root = removeRoll(root, roll, &found);
            printf(found ? "Deleted.\n" : "Roll not found.\n");
            break;
        case 3:
            printf("Enter roll number to search: ");
            scanf("%d", &roll);
            printf(search(root, roll) ? "Student found.\n" : "Student not found.\n");
            break;
        case 4:
            printf("Inorder:   "); inorder(root);   printf("\n");
            printf("Preorder:  "); preorder(root);  printf("\n");
            printf("Postorder: "); postorder(root); printf("\n");
            break;
        case 0: break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    freeTree(root);
    return 0;
}
