#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Simple dynamic array / adjacency list structure
typedef struct {
    int *data;
    int size;
    int capacity;
} Vector;

void init_vector(Vector *v) {
    v->size = 0;
    v->capacity = 4;
    v->data = (int *)malloc(v->capacity * sizeof(int));
}

void push_vector(Vector *v, int val) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
    }
    v->data[v->size++] = val;
}

void free_vector(Vector *v) {
    free(v->data);
}

// Global Graph representation
int n, m;
Vector *adj;
Vector *adj_rev;
Vector *adj_scc;

bool *visited;
int *order_stack;
int stack_top = 0;

int *component;
int *scc_rep;
int scc_count = 0;

// First DFS for Kosaraju's algorithm
void dfs1(int v) {
    visited[v] = true;
    for (int i = 0; i < adj[v].size; ++i) {
        int u = adj[v].data[i];
        if (!visited[u]) dfs1(u);
    }
    order_stack[stack_top++] = v;
}

// Second DFS for Kosaraju's algorithm
void dfs2(int v, int c) {
    visited[v] = true;
    component[v] = c;
    for (int i = 0; i < adj_rev[v].size; ++i) {
        int u = adj_rev[v].data[i];
        if (!visited[u]) dfs2(u, c);
    }
}

// Trace down a path to find a reachable sink in the DAG
int find_sink(int u, const int *out_deg, int *memo) {
    if (out_deg[u] == 0) return u;
    if (memo[u] != -1) return memo[u];
    
    for (int i = 0; i < adj_scc[u].size; ++i) {
        int v = adj_scc[u].data[i];
        int res = find_sink(v, out_deg, memo);
        if (res != -1) return memo[u] = res;
    }
    return -1;
}

// Simple hash map logic for deduplicating edges in condensed graph
typedef struct {
    long long key;
} EdgeHash;

int compare_long(const void *a, const void *b) {
    long long arg1 = *(const long long*)a;
    long long arg2 = *(const long long*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main() {
    if (scanf("%d %d", &n, &m) != 2) return 0;

    adj = (Vector *)malloc((n + 1) * sizeof(Vector));
    adj_rev = (Vector *)malloc((n + 1) * sizeof(Vector));
    for (int i = 1; i <= n; ++i) {
        init_vector(&adj[i]);
        init_vector(&adj_rev[i]);
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            push_vector(&adj[u], v);
            push_vector(&adj_rev[v], u);
        }
    }

    // Step 1: Kosaraju's Algorithm to find Strongly Connected Components
    visited = (bool *)calloc(n + 1, sizeof(bool));
    order_stack = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) dfs1(i);
    }

    for (int i = 1; i <= n; ++i) visited[i] = false;
    component = (int *)malloc((n + 1) * sizeof(int));
    scc_rep = (int *)malloc((n + 1) * sizeof(int));

    while (stack_top > 0) {
        int v = order_stack[--stack_top];
        if (!visited[v]) {
            scc_rep[scc_count] = v; // Track head representative element
            dfs2(v, scc_count);
            scc_count++;
        }
    }

    // If already strongly connected, no new flights are needed
    if (scc_count == 1) {
        printf("0\n");
        return 0;
    }

    // Step 2: Build the condensed DAG graph
    adj_scc = (Vector *)malloc(scc_count * sizeof(Vector));
    int *in_deg = (int *)calloc(scc_count, sizeof(int));
    int *out_deg = (int *)calloc(scc_count, sizeof(int));
    for (int i = 0; i < scc_count; ++i) init_vector(&adj_scc[i]);

    // Fast sorting container to uniqueness filter compressed graph edges
    long long *edge_keys = (long long *)malloc(m * sizeof(long long));
    int edge_key_cnt = 0;

    for (int u = 1; u <= n; ++u) {
        for (int i = 0; i < adj[u].size; ++i) {
            int v = adj[u].data[i];
            int comp_u = component[u];
            int comp_v = component[v];
            if (comp_u != comp_v) {
                edge_keys[edge_key_cnt++] = ((long long)comp_u << 32) | comp_v;
            }
        }
    }

    qsort(edge_keys, edge_key_cnt, sizeof(long long), compare_long);

    for (int i = 0; i < edge_key_cnt; ++i) {
        if (i == 0 || edge_keys[i] != edge_keys[i - 1]) {
            int comp_u = (int)(edge_keys[i] >> 32);
            int comp_v = (int)(edge_keys[i] & 0xFFFFFFFF);
            push_vector(&adj_scc[comp_u], comp_v);
            out_deg[comp_u]++;
            in_deg[comp_v]++;
        }
    }
    free(edge_keys);

    // Identify DAG terminal categories
    Vector sources, sinks;
    init_vector(&sources);
    init_vector(&sinks);
    for (int i = 0; i < scc_count; ++i) {
        if (in_deg[i] == 0) push_vector(&sources, i);
        if (out_deg[i] == 0) push_vector(&sinks, i);
    }

    // Step 3: Match tracking arrays
    int *memo = (int *)malloc(scc_count * sizeof(int));
    for (int i = 0; i < scc_count; ++i) memo[i] = -1;

    int *matched_sink = (int *)malloc(sources.size * sizeof(int));
    bool *sink_covered = (bool *)calloc(scc_count, sizeof(bool));

    for (int i = 0; i < sources.size; ++i) {
        matched_sink[i] = find_sink(sources.data[i], out_deg, memo);
        sink_covered[matched_sink[i]] = true;
    }

    Vector uncovered_sinks;
    init_vector(&uncovered_sinks);
    for (int i = 0; i < sinks.size; ++i) {
        int snk = sinks.data[i];
        if (!sink_covered[snk]) push_vector(&uncovered_sinks, snk);
    }

    // Align tracking groups into final balanced structures
    Vector src_list, snk_list;
    init_vector(&src_list);
    init_vector(&snk_list);

    for (int i = 0; i < sources.size; ++i) {
        push_vector(&src_list, sources.data[i]);
        push_vector(&snk_list, matched_sink[i]);
    }
    for (int i = 0; i < uncovered_sinks.size; ++i) {
        push_vector(&snk_list, uncovered_sinks.data[i]);
    }

    while (src_list.size < snk_list.size) {
        push_vector(&src_list, sources.data[0]);
    }
    while (snk_list.size < src_list.size) {
        push_vector(&snk_list, sinks.data[0]);
    }

    int k = src_list.size;
    printf("%d\n", k);

    // Step 4: Output structural cycle adjustments
    for (int i = 0; i < k; ++i) {
        int u = scc_rep[snk_list.data[i]];
        int v = scc_rep[src_list.data[(i + 1) % k]];
        printf("%d %d\n", u, v);
    }

    // Cleanup memory allocations
    for (int i = 1; i <= n; ++i) {
        free_vector(&adj[i]);
        free_vector(&adj_rev[i]);
    }
    for (int i = 0; i < scc_count; ++i) free_vector(&adj_scc[i]);
    free(adj); free(adj_rev); free(adj_scc);
    free(visited); free(order_stack); free(component); free(scc_rep);
    free(in_deg); free(out_deg); free(memo); free(matched_sink); free(sink_covered);
    free_vector(&sources); free_vector(&sinks); free_vector(&uncovered_sinks);
    free_vector(&src_list); free_vector(&snk_list);

    return 0;
}
