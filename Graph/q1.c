#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent each road
typedef struct {
    int u;
    int v;
    unsigned long long mask;
} Road;

// Global/static arrays to avoid repeated runtime heap allocation overhead
int parent[100005];
Road roads[100005];
unsigned long long c[65];

// Standard DSU Find operation with path compression
int find_set(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find_set(parent[i]);
}

// Function to check if the graph is fully connected given an available token mask
bool is_connected(int n, int m, unsigned long long available_mask) {
    // Reset DSU structures
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    int components = n;

    for (int i = 0; i < m; i++) {
        // A road is usable if all its required tokens are inside the available_mask
        if ((roads[i].mask & available_mask) == roads[i].mask) {
            int root_u = find_set(roads[i].u);
            int root_v = find_set(roads[i].v);
            
            if (root_u != root_v) {
                parent[root_u] = root_v;
                components--;
                // Early termination condition
                if (components == 1) {
                    return true;
                }
            }
        }
    }
    return components == 1;
}

int main() {
    int n, m, k;
    if (scanf("%d %d %d", &n, &m, &k) != 3) return 0;

    // Read the costs of tokens (1-indexed)
    for (int i = 1; i <= k; i++) {
        scanf("%llu", &c[i]);
    }

    // Read roads and build their token requirements bitmask
    for (int i = 0; i < m; i++) {
        int u, v, l;
        scanf("%d %d %d", &u, &v, &l);
        
        unsigned long long road_mask = 0;
        for (int j = 0; j < l; j++) {
            int token_idx;
            scanf("%d", &token_idx);
            road_mask |= (1ULL << (token_idx - 1));
        }
        
        roads[i].u = u;
        roads[i].v = v;
        roads[i].mask = road_mask;
    }

    // Baseline sanity check: can we even connect the graph using ALL tokens?
    unsigned long long all_tokens_mask = (k == 64) ? ~0ULL : ((1ULL << k) - 1);
    if (!is_connected(n, m, all_tokens_mask)) {
        printf("-1\n");
        return 0;
    }

    unsigned long long chosen_mask = 0;

    // Process from the most expensive token down to the cheapest
    for (int i = k; i >= 1; i--) {
        // Test mask contains tokens already permanently chosen + all tokens smaller than i
        unsigned long long test_mask = chosen_mask | ((1ULL << (i - 1)) - 1);
        
        // If graph fails to connect without token i, token i becomes mandatory
        if (!is_connected(n, m, test_mask)) {
            chosen_mask |= (1ULL << (i - 1));
        }
    }

    // Compute the cumulative minimum cost
    unsigned long long total_cost = 0;
    for (int i = 1; i <= k; i++) {
        if ((chosen_mask >> (i - 1)) & 1) {
            total_cost += c[i];
        }
    }

    printf("%llu\n", total_cost);

    return 0;
}
