#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 200005

// Structure for the adjacency list edges
typedef struct {
    int to;
    int next;
} Edge;

Edge edges[2 * MAXN];
int head[MAXN];
int edge_cnt = 0;

bool matched[MAXN];
int matching_count = 0;

// Function to add an undirected edge to the adjacency list
void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

// Greedy DFS to match bottom-up
void dfs(int node, int parent) {
    for (int e = head[node]; e != -1; e = edges[e].next) {
        int neighbor = edges[e].to;
        if (neighbor != parent) {
            dfs(neighbor, node);
        }
    }
    
    // Greedily match with parent if both current node and parent are unmatched
    if (parent != 0 && !matched[node] && !matched[parent]) {
        matched[node] = true;
        matched[parent] = true;
        matching_count++;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    // Initialize head array for adjacency list
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        matched[i] = false;
    }
    
    // Read n-1 edges
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            add_edge(u, v);
            add_edge(v, u);
        }
    }
    
    // Run DFS starting from root 1 (parent 0)
    dfs(1, 0);
    
    // Output the maximum number of matching edges
    printf("%d\n", matching_count);
    
    return 0;
}
