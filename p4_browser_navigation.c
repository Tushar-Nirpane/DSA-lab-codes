#include <stdio.h>
#include <string.h>

#define MAX 100
#define URL_LEN 100

typedef struct {
    char items[MAX][URL_LEN];
    int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }
int isEmpty(const Stack *s) { return s->top == -1; }
int isFull(const Stack *s) { return s->top == MAX - 1; }

void push(Stack *s, const char *url) {
    if (isFull(s)) { printf("Stack overflow.\n"); return; }
    strcpy(s->items[++s->top], url);
}

int pop(Stack *s, char *out) {
    if (isEmpty(s)) return 0;
    strcpy(out, s->items[s->top--]);
    return 1;
}

char current[URL_LEN] = "home";
Stack backStack, forwardStack;

void visit(const char *url) {
    push(&backStack, current);
    strcpy(current, url);
    initStack(&forwardStack);
    printf("Visited: %s\n", current);
}

void goBack(void) {
    char prev[URL_LEN];
    if (!pop(&backStack, prev)) { printf("No page to go back to.\n"); return; }
    push(&forwardStack, current);
    strcpy(current, prev);
    printf("Back to: %s\n", current);
}

void goForward(void) {
    char next[URL_LEN];
    if (!pop(&forwardStack, next)) { printf("No page to go forward to.\n"); return; }
    push(&backStack, current);
    strcpy(current, next);
    printf("Forward to: %s\n", current);
}

int main(void) {
    int choice;
    char url[URL_LEN];

    initStack(&backStack);
    initStack(&forwardStack);

    do {
        printf("\n1.Visit new page 2.Back 3.Forward 4.Display current 0.Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        getchar();
        switch (choice) {
        case 1:
            printf("Enter URL: ");
            fgets(url, URL_LEN, stdin);
            url[strcspn(url, "\n")] = '\0';
            visit(url);
            break;
        case 2: goBack(); break;
        case 3: goForward(); break;
        case 4: printf("Current page: %s\n", current); break;
        case 0: break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}
