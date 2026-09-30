#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
typedef struct {
    int u, v, weight;
} Edge;

// DSU Structure arrays (sized dynamically per test case)
int *parent;
int *rankArr;

// DSU Functions
void init_dsu(int n) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }
}

int find_set(int i) {
    if (parent[i] == i)
        return i;
    // Path compression optimization
    return parent[i] = find_set(parent[i]);
}

int union_sets(int i, int j) {
    int root_i = find_set(i);
    int root_j = find_set(j);
    
    if (root_i != root_j) {
        // Union by rank optimization
        if (rankArr[root_i] < rankArr[root_j]) {
            parent[root_i] = root_j;
        } else if (rankArr[root_i] > rankArr[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rankArr[root_i]++;
        }
        return 1; // Successfully united
    }
    return 0; // Already in the same component
}

// Comparator function to sort edges in DESCENDING order of weights
int compare_edges(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeB->weight - edgeA->weight;
}

void solve() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return;
    
    Edge *edges = (Edge *)malloc(m * sizeof(Edge));
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }
    
    // Sort edges in descending order
    qsort(edges, m, sizeof(Edge), compare_edges);
    
    // Allocate space for DSU elements up to N nodes
    parent = (int *)malloc((n + 1) * sizeof(int));
    rankArr = (int *)malloc((n + 1) * sizeof(int));
    init_dsu(n);
    
    long long max_spanning_weight = 0; // Using long long to avoid potential integer overflow
    int edges_included = 0;
    
    for (int i = 0; i < m; i++) {
        if (union_sets(edges[i].u, edges[i].v)) {
            max_spanning_weight += edges[i].weight;
            edges_included++;
            // A tree with N vertices always contains exactly N - 1 edges
            if (edges_included == n - 1) {
                break;
            }
        }
    }
    
    printf("%lld\n", max_spanning_weight);
    
    // Free allocated memory for the current testcase
    free(edges);
    free(parent);
    free(rankArr);
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
