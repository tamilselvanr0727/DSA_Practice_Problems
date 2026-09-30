#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 505
#define MAXM 2005
#define INF 1e9

// Structure to represent a directed edge in the residual graph
typedef struct {
    int to;
    int cap;
    int flow;
    int rev; // Index of the reverse edge in the adjacency list of 'to'
} Edge;

// Global graph structures to prevent stack overflow
Edge adj[MAXN][MAXM];
int adj_size[MAXN];

int parent_node[MAXN];
int parent_edge[MAXN];
int path[MAXN];

// Function to add a directed edge with capacity 1
void add_edge(int from, int to) {
    // Forward edge
    adj[from][adj_size[from]] = (Edge){to, 1, 0, adj_size[to]};
    // Backward residual edge
    adj[to][adj_size[to]] = (Edge){from, 0, 0, adj_size[from]};
    
    adj_size[from]++;
    adj_size[to]++;
}

// Breadth-First Search to find an augmenting path
bool bfs(int source, int sink, int n) {
    for (int i = 1; i <= n; i++) {
        parent_node[i] = -1;
    }
    
    int queue[MAXN];
    int head = 0, tail = 0;
    
    queue[tail++] = source;
    parent_node[source] = source;
    
    while (head < tail) {
        int u = queue[head++];
        if (u == sink) return true;
        
        for (int i = 0; i < adj_size[u]; i++) {
            Edge e = adj[u][i];
            if (parent_node[e.to] == -1 && e.cap - e.flow > 0) {
                parent_node[e.to] = u;
                parent_edge[e.to] = i;
                queue[tail++] = e.to;
            }
        }
    }
    return parent_node[sink] != -1;
}

// Edmonds-Karp algorithm to compute Max Flow
int edmonds_karp(int source, int sink, int n) {
    int max_flow = 0;
    
    while (bfs(source, sink, n)) {
        int path_flow = INF;
        
        // Find the maximum flow possible along the path found by BFS
        for (int v = sink; v != source; v = parent_node[v]) {
            int u = parent_node[v];
            int idx = parent_edge[v];
            if (adj[u][idx].cap - adj[u][idx].flow < path_flow) {
                path_flow = adj[u][idx].cap - adj[u][idx].flow;
            }
        }
        
        // Update capacities of forward and reverse edges
        for (int v = sink; v != source; v = parent_node[v]) {
            int u = parent_node[v];
            int idx = parent_edge[v];
            int rev_idx = adj[u][idx].rev;
            adj[u][idx].flow += path_flow;
            adj[v][rev_idx].flow -= path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

// Trace and print the distinct paths from room 1 to room n
void print_paths(int source, int sink, int max_flow) {
    printf("%d\n", max_flow);
    
    for (int f = 0; f < max_flow; f++) {
        int curr = source;
        int path_len = 0;
        path[path_len++] = curr;
        
        while (curr != sink) {
            for (int i = 0; i < adj_size[curr]; i++) {
                // If it is an original teleporter (cap == 1) and was used (flow == 1)
                if (adj[curr][i].cap == 1 && adj[curr][i].flow == 1) {
                    adj[curr][i].flow = 0; // Consume the edge so it isn't reused
                    curr = adj[curr][i].to;
                    path[path_len++] = curr;
                    break;
                }
            }
        }
        
        // Print route length followed by the room sequence
        printf("%d\n", path_len);
        for (int i = 0; i < path_len; i++) {
            printf("%d%c", path[i], (i == path_len - 1) ? '\n' : ' ');
        }
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    // Reset adjacency counts
    memset(adj_size, 0, sizeof(adj_size));
    
    for (int i = 0; i < m; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            add_edge(u, v);
        }
    }
    
    int source = 1;
    int sink = n;
    
    int max_flow = edmonds_karp(source, sink, n);
    print_paths(source, sink, max_flow);
    
    return 0;
}
