#include <stdio.h>
#include <string.h>

#define MAX_USERS 50
#define MAX_NAME  30

char users[MAX_USERS][MAX_NAME];
int adj[MAX_USERS][MAX_USERS];
int userCount = 0;

int getUser(const char *name) {
    for (int i = 0; i < userCount; i++)
        if (strcmp(users[i], name) == 0) return i;
    if (userCount == MAX_USERS) return -1;
    strcpy(users[userCount], name);
    return userCount++;
}

void addConnection(const char *a, const char *b) {
    int i = getUser(a), j = getUser(b);
    if (i < 0 || j < 0) { printf("User limit reached.\n"); return; }
    if (i == j) { printf("A user cannot connect to self.\n"); return; }
    adj[i][j] = adj[j][i] = 1;
    printf("Connected %s and %s.\n", a, b);
}

void bfs(int start) {
    int visited[MAX_USERS] = {0}, queue[MAX_USERS], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;
    printf("BFS from %s: ", users[start]);
    while (front < rear) {
        int u = queue[front++];
        printf("%s ", users[u]);
        for (int v = 0; v < userCount; v++)
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
    }
    printf("\n");
}

void dfsUtil(int u, int visited[]) {
    visited[u] = 1;
    printf("%s ", users[u]);
    for (int v = 0; v < userCount; v++)
        if (adj[u][v] && !visited[v])
            dfsUtil(v, visited);
}

void dfs(int start) {
    int visited[MAX_USERS] = {0};
    printf("DFS from %s: ", users[start]);
    dfsUtil(start, visited);
    printf("\n");
}

int main(void) {
    int choice;
    char a[MAX_NAME], b[MAX_NAME];

    do {
        printf("\n1.Add connection 2.BFS 3.DFS 0.Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:
            printf("Enter two user names: ");
            scanf("%29s %29s", a, b);
            addConnection(a, b);
            break;
        case 2:
        case 3:
            printf("Enter start user: ");
            scanf("%29s", a);
            {
                int s = -1;
                for (int i = 0; i < userCount; i++)
                    if (strcmp(users[i], a) == 0) s = i;
                if (s < 0) { printf("User not found.\n"); break; }
                if (choice == 2) bfs(s); else dfs(s);
            }
            break;
        case 0: break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}
