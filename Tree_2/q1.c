#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

// Flattened Adjacency list structures to optimize space usage
int head1[MAXN], head2[MAXN];
int next_edge1[2 * MAXN], to1[2 * MAXN];
int next_edge2[2 * MAXN], to2[2 * MAXN];
int edge_cnt1, edge_cnt2;

// Arrays for tracking children and custom subtree values
int children_ids[MAXN];
int hash_val[MAXN];

// Add directional edges to the trees
void add_edge1(int u, int v) {
    to1[edge_cnt1] = v;
    next_edge1[edge_cnt1] = head1[u];
    head1[u] = edge_cnt1++;
}

void add_edge2(int u, int v) {
    to2[edge_cnt2] = v;
    next_edge2[edge_cnt2] = head2[u];
    head2[u] = edge_cnt2++;
}

// Basic comparison function for qsort
int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// 64-bit custom combination mixing function to simulate dynamic string/tuple sorting hashes
unsigned long long mix_hash(unsigned long long a, unsigned long long b) {
    a ^= b + 0x9e3779b97f4a7c15ULL + (a << 6) + (a >> 2);
    return a;
}

// DFS function to hash structural layouts 
unsigned long long dfs1(int node, int parent) {
    int start_idx = children_ids[node]; 
    int child_count = 0;
    
    // Find all children
    for (int e = head1[node]; e != -1; e = next_edge1[e]) {
        int neighbor = to1[e];
        if (neighbor != parent) {
            child_count++;
        }
    }
    
    // Collect child structures dynamically
    int *local_arr = (int *)malloc(child_count * sizeof(int));
    int idx = 0;
    for (int e = head1[node]; e != -1; e = next_edge1[e]) {
        int neighbor = to1[e];
        if (neighbor != parent) {
            local_arr[idx++] = dfs1(neighbor, node);
        }
    }
    
    // Sort identifiers to force canonical order independence between siblings
    qsort(local_arr, child_count, sizeof(int), compare_ints);
    
    // Compute combined structural hash block
    unsigned long long structural_hash = 1234567891011ULL;
    for (int i = 0; i < child_count; i++) {
        structural_hash = mix_hash(structural_hash, local_arr[i]);
    }
    
    free(local_arr);
    return structural_hash;
}

unsigned long long dfs2(int node, int parent) {
    int child_count = 0;
    for (int e = head2[node]; e != -1; e = next_edge2[e]) {
        int neighbor = to2[e];
        if (neighbor != parent) {
            child_count++;
        }
    }
    
    int *local_arr = (int *)malloc(child_count * sizeof(int));
    int idx = 0;
    for (int e = head2[node]; e != -1; e = next_edge2[e]) {
        int neighbor = to2[e];
        if (neighbor != parent) {
            local_arr[idx++] = dfs2(neighbor, node);
        }
    }
    
    qsort(local_arr, child_count, sizeof(int), compare_ints);
    
    unsigned long long structural_hash = 1234567891011ULL;
    for (int i = 0; i < child_count; i++) {
        structural_hash = mix_hash(structural_hash, local_arr[i]);
    }
    
    free(local_arr);
    return structural_hash;
}

void solve() {
    int t;
    if (scanf("%d", &t) != 1) return;
    
    while (t--) {
        int n;
        if (scanf("%d", &n) != 1) break;
        
        // Reset Adjacency List pointers
        edge_cnt1 = 0;
        edge_cnt2 = 0;
        for (int i = 1; i <= n; i++) {
            head1[i] = -1;
            head2[i] = -1;
        }
        
        // Parse Edges for Tree 1
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            add_edge1(u, v);
            add_edge1(v, u);
        }
        
        // Parse Edges for Tree 2
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            add_edge2(u, v);
            add_edge2(v, u);
        }
        
        // Compute canonical baseline signatures starting from Root 1
        unsigned long long hash1 = dfs1(1, 0);
        unsigned long long hash2 = dfs2(1, 0);
        
        if (hash1 == hash2) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int main() {
    solve();
    return 0;
}
