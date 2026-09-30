#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INF 1e9
#define MAXN 505
#define MAXM 1005

// Structure to represent an edge in the adjacency list
typedef struct {
    int to;
    int next;
} Edge;

// Global structures for the residual graph
Edge edges[MAXM * 2];
int head[MAXN];
int edge_count = 0;

int capacity[MAXN][MAXN];
int parent_node[MAXN];
bool visited[MAXN];

// Storage for original inputs to reconstruct the minimum cut
int orig_u[MAXM];
int orig_v[MAXM];

// Utility function to add directional graph edges
void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

// Breadth-First Search to find an augmenting path in the residual graph
int bfs(int s, int t, int n) {
    for (int i = 1; i <= n; i++) {
        parent_node[i] = -1;
    }
    parent_node[s] = -2;

    // Queue management using plain arrays
    int q[MAXN * 2];
    int flow_arr[MAXN * 2];
    int front = 0, rear = 0;

    q[rear] = s;
    flow_arr[rear] = INF;
    rear++;

    while (front < rear) {
        int cur = q[front];
        int flow = flow_arr[front];
        front++;

        for (int e = head[cur]; e != -1; e = edges[e].next) {
            int next = edges[e].to;
            if (parent_node[next] == -1 && capacity[cur][next] > 0) {
                parent_node[next] = cur;
                int new_flow = (flow < capacity[cur][next]) ? flow : capacity[cur][next];
                
                if (next == t) return new_flow;
                
                q[rear] = next;
                flow_arr[rear] = new_flow;
                rear++;
            }
        }
    }
    return 0;
}

// Edmonds-Karp maximum flow algorithm
int max_flow(int s, int t, int n) {
    int flow = 0;
    int new_flow;

    while ((new_flow = bfs(s, t, n)) > 0) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent_node[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

// Depth-First Search to find all nodes reachable within the final graph structure
void dfs(int s) {
    visited[s] = true;
    for (int e = head[s]; e != -1; e = edges[e].next) {
        int next = edges[e].to;
        if (!visited[next] && capacity[s][next] > 0) {
            dfs(next);
        }
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // Initialize adjacency list heads
    memset(head, -1, sizeof(head));
    memset(capacity, 0, sizeof(capacity));

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &orig_u[i], &orig_v[i]);
        int u = orig_u[i];
        int v = orig_v[i];

        add_edge(u, v);
        add_edge(v, u);

        // Streets are bidirectional and have an individual capacity unit of 1
        capacity[u][v] += 1;
        capacity[v][u] += 1;
    }

    // Determine the minimum streets to close via the Max Flow logic
    int min_cut_val = max_flow(1, n, n);
    printf("%d\n", min_cut_val);

    // Track accessible graph areas
    memset(visited, 0, sizeof(visited));
    dfs(1);

    // Identify and print original streets separating the visited and unvisited components
    for (int i = 0; i < m; i++) {
        int u = orig_u[i];
        int v = orig_v[i];
        if ((visited[u] && !visited[v]) || (visited[v] && !visited[u])) {
            printf("%d %d\n", u, v);
        }
    }

    return 0;
}
