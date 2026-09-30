#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005

int parent_node[MAXN];
int dist_to_parent[MAXN];

// Initialize the DSU structures
void init_dsu(int n) {
    for (int i = 0; i <= n; i++) {
        parent_node[i] = i;
        dist_to_parent[i] = 0;
    }
}

// Find function with path compression to maintain XOR sums
int find_set(int v) {
    if (v == parent_node[v]) {
        return v;
    }
    int root = find_set(parent_node[v]);
    // Accumulate the XOR weights up to the absolute root
    dist_to_parent[v] ^= dist_to_parent[parent_node[v]];
    return parent_node[v] = root;
}

// Attempts to add an edge between u and v with weight x
bool union_sets(int u, int v, int x) {
    int root_u = find_set(u);
    int root_v = find_set(v);

    if (root_u != root_v) {
        // Link the root of u's component to the root of v's component
        parent_node[root_u] = root_v;
        // Calculate the needed weight offset for the root bridge
        dist_to_parent[root_u] = x ^ dist_to_parent[u] ^ dist_to_parent[v];
        return true;
    } else {
        // u and v are already in the same component.
        // A cycle is formed; verify if its total XOR sum equals 1.
        int existing_path_xor = dist_to_parent[u] ^ dist_to_parent[v];
        return existing_path_xor == (x ^ 1);
    }
}

int main() {
    // Fast I/O for performance
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    init_dsu(n);

    for (int i = 0; i < q; i++) {
        int u, v, x;
        scanf("%d %d %d", &u, &v, &x);

        if (union_sets(u, v, x)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
