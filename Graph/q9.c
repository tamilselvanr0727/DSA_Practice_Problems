#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 505
#define INF 1e9

// Residual capacity matrix: capacity[u][v] represents available capacity from u to v
int capacity[MAXN][MAXN];
int parent[MAXN];

// Breadth-First Search to find an augmenting path
bool bfs(int n, int s, int t) {
    bool visited[MAXN];
    memset(visited, 0, sizeof(visited));
    
    int queue[MAXN];
    int head = 0, tail = 0;
    
    queue[tail++] = s;
    visited[s] = true;
    parent[s] = -1;
    
    while (head < tail) {
        int u = queue[head++];
        
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && capacity[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                if (v == t) return true;
                queue[tail++] = v;
            }
        }
    }
    return false;
}

// Edmonds-Karp Max Flow algorithm
int edmonds_karp(int n, int s, int t) {
    int flow = 0;
    
    while (bfs(n, s, t)) {
        // Find the minimum residual capacity along the path found by BFS
        int path_flow = INF;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (capacity[u][v] < path_flow) {
                path_flow = capacity[u][v];
            }
        }
        
        // Update residual capacities of the edges and reverse edges
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }
        
        flow += path_flow;
    }
    return flow;
}

// DFS to trace and recover the paths
void find_path(int u, int t, int n, int *path, int *path_size) {
    path[(*path_size)++] = u;
    if (u == t) return;
    
    for (int v = 1; v <= n; v++) {
        // Since original capacity was 1, if capacity[v][u] == 1, 
        // it means 1 unit of flow went from u to v.
        if (capacity[v][u] == 1) {
            capacity[v][u] = 0; // Consume this flow path so it isn't reused
            find_path(v, t, n, path, path_size);
            return;
        }
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    // Initialize capacities to 0
    memset(capacity, 0, sizeof(capacity));
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        capacity[u][v] = 1; // Direct teleporter has capacity 1
    }
    
    // Compute max flow from source (1) to sink (n)
    int max_days = edmonds_karp(n, 1, n);
    printf("%d\n", max_days);
    
    // Track and print each path
    int path[MAXN];
    for (int i = 0; i < max_days; i++) {
        int path_size = 0;
        find_path(1, n, n, path, &path_size);
        
        printf("%d\n", path_size);
        for (int j = 0; j < path_size; j++) {
            printf("%d%s", path[j], (j == path_size - 1) ? "" : " ");
        }
        printf("\n");
    }
    
    return 0;
}
