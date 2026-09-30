#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structures for the Forward Star graph representation
typedef struct {
    int to;
    int next;
} Edge;

// Fixed array bounds based on problem constraints (N <= 10^5, M <= 2*10^5)
Edge edges[400005]; // 2 * M because roads are bidirectional
int head[100005];
int edge_cnt = 0;

bool visited[100005];
int representatives[100005];
int comp_cnt = 0;

// Explicit stack structure for Iterative DFS to avoid Stack Overflow
int dfs_stack[100005];

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

// Iterative DFS ensures safe execution even with deep linear graph paths
void dfs_iterative(int start_node) {
    int top = 0;
    dfs_stack[top] = start_node;
    visited[start_node] = true;

    while (top >= 0) {
        int node = dfs_stack[top--];

        for (int e = head[node]; e != -1; e = edges[e].next) {
            int neighbor = edges[e].to;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dfs_stack[++top] = neighbor;
            }
        }
    }
}

int main() {
    int n, m;
    // Fast I/O verification
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // Initialize adjacency list heads
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        visited[i] = false;
    }

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            add_edge(u, v);
            add_edge(v, u);
        }
    }

    // Find all connected components
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            representatives[comp_cnt++] = i;
            dfs_iterative(i);
        }
    }

    // Output results
    int required_roads = comp_cnt - 1;
    printf("%d\n", required_roads);

    for (int i = 0; i < required_roads; i++) {
        printf("%d %d\n", representatives[i], representatives[i + 1]);
    }

    return 0;
}
