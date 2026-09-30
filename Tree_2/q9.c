#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

// Structure for adjacency list representation of the tree
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj[MAXN];
int counts[MAXN][26];
char s[MAXN];
int visited[MAXN];

// Helper function to add an undirected edge to the adjacency list
void add_edge(int u, int v) {
    Node* node1 = (Node*)malloc(sizeof(Node));
    node1->vertex = v;
    node1->next = adj[u];
    adj[u] = node1;

    Node* node2 = (Node*)malloc(sizeof(Node));
    node2->vertex = u;
    node2->next = adj[v];
    adj[v] = node2;
}

// Bottom-up DFS to precompute character counts in every subtree
void dfs(int u) {
    visited[u] = 1;
    
    // Account for the character at the current node itself
    int self_char = s[u - 1] - 'a';
    counts[u][self_char] = 1;

    Node* curr = adj[u];
    while (curr != NULL) {
        int v = curr->vertex;
        if (!visited[v]) {
            dfs(v);
            // Accumulate character frequencies from the child node's subtree
            for (int i = 0; i < 26; i++) {
                counts[u][i] += counts[v][i];
            }
        }
        curr = curr->next;
    }
}

// Custom fast I/O function to read integers efficiently
int read_int() {
    int val = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        val = val * 10 + (c - '0');
        c = getchar();
    }
    return val;
}

int main() {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;

    // Read the string containing lowercase characters for the nodes
    if (scanf("%s", s) != 1) return 0;

    // Initialize adjacency list headers
    for (int i = 1; i <= N; i++) {
        adj[i] = NULL;
    }

    // Build the tree layout from the input edges
    for (int i = 0; i < N - 1; i++) {
        int u = read_int();
        int v = read_int();
        add_edge(u, v);
    }

    // Precompute character metrics starting from the root node (1)
    memset(visited, 0, sizeof(visited));
    memset(counts, 0, sizeof(counts));
    dfs(1);

    // Process all Q queries instantaneously in O(1)
    for (int i = 0; i < Q; i++) {
        int u = read_int();
        
        // Skip whitespace characters to accurately fetch the target character
        char c = getchar();
        while (c < 'a' || c > 'z') {
            c = getchar();
        }

        int char_idx = c - 'a';
        printf("%d\n", counts[u][char_idx]);
    }

    // Free allocated linked-list memory to clean up heap space
    for (int i = 1; i <= N; i++) {
        Node* curr = adj[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    return 0;
}
