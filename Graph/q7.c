#include <stdio.h>
#include <stdlib.h>

// Global variables to track the state
int parent[100005];
int sz[100005];
int num_components;
int max_component_size;

// Find operation with Path Compression
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]); // Path compression
}

// Union operation by size
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    
    if (a != b) {
        // Union by size: attach the smaller tree under the larger tree
        if (sz[a] < sz[b]) {
            int temp = a;
            a = b;
            b = temp;
        }
        parent[b] = a;
        sz[a] += sz[b];
        
        // Update global tracking variables
        num_components--;
        if (sz[a] > max_component_size) {
            max_component_size = sz[a];
        }
    }
}

int main() {
    int n, m;
    
    // Fast I/O reading the initial counts
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    // Initialization: each city is its own component
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    
    num_components = n;
    max_component_size = 1;
    
    // Process each road day by day
    for (int i = 0; i < m; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        
        union_sets(u, v);
        
        // Efficiently output the result using standard fast output formatting
        printf("%d %d\n", num_components, max_component_size);
    }
    
    return 0;
}
