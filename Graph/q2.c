#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in the adjacency list
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

int n, m;
Vector *adj;
Vector *adj_rev;
bool *used;
int *order;
int order_idx = 0;
int *comp;

int get_node(int x) {
    if (x > 0) return x - 1;
    return m + (-x) - 1;
}

int get_neg(int x) {
    if (x < m) return x + m;
    return x - m;
}

void add_disjunction(int a, int b) {
    int na = get_neg(a);
    int nb = get_neg(b);
    push_vector(&adj[na], b);
    push_vector(&adj_rev[b], na);
    push_vector(&adj[nb], a);
    push_vector(&adj_rev[a], nb);
}

// First DFS pass to find the topological order of the system
void dfs1(int v) {
    used[v] = true;
    for (int i = 0; i < adj[v].size; i++) {
        int u = adj[v].data[i];
        if (!used[u]) {
            dfs1(u);
        }
    }
    order[order_idx++] = v;
}

// Second DFS pass on the transposed graph to mark components
void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int i = 0; i < adj_rev[v].size; i++) {
        int u = adj_rev[v].data[i];
        if (comp[u] == -1) {
            dfs2(u, cl);
        }
    }
}

int main() {
    if (scanf("%d %d", &n, &m) != 2) return 0;

    int num_nodes = 2 * m;

    adj = (Vector *)malloc(num_nodes * sizeof(Vector));
    adj_rev = (Vector *)malloc(num_nodes * sizeof(Vector));
    for (int i = 0; i < num_nodes; i++) {
        init_vector(&adj[i]);
        init_vector(&adj_rev[i]);
    }

    // Read the inputs and populate the implication graphs
    for (int i = 0; i < n; i++) {
        char sign1, sign2;
        int u, v;
        // Read formatting carefully ensuring any potential space buffers are ignored
        scanf(" %c%d %c%d", &sign1, &u, &sign2, &v);
        if (sign1 == '-') u = -u;
        if (sign2 == '-') v = -v;
        add_disjunction(get_node(u), get_node(v));
    }

    used = (bool *)calloc(num_nodes, sizeof(bool));
    order = (int *)malloc(num_nodes * sizeof(int));

    for (int i = 0; i < num_nodes; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }

    comp = (int *)malloc(num_nodes * sizeof(int));
    for (int i = 0; i < num_nodes; i++) comp[i] = -1;

    int cl = 0;
    for (int i = 0; i < num_nodes; i++) {
        int v = order[num_nodes - 1 - i];
        if (comp[v] == -1) {
            dfs2(v, cl++);
        }
    }

    // Verify consistency and extract the valid assignment values
    bool possible = true;
    char *assignment = (char *)malloc(m * sizeof(char));

    for (int i = 0; i < m; i++) {
        if (comp[i] == comp[i + m]) {
            possible = false;
            break;
        }
        assignment[i] = (comp[i] > comp[i + m]) ? '+' : '-';
    }

    if (!possible) {
        printf("IMPOSSIBLE\n");
    } else {
        for (int i = 0; i < m; i++) {
            printf("%c%s", assignment[i], (i == m - 1) ? "" : " ");
        }
        printf("\n");
    }

    // Clean up allocated memory
    for (int i = 0; i < num_nodes; i++) {
        free_vector(&adj[i]);
        free_vector(&adj_rev[i]);
    }
    free(adj);
    free(adj_rev);
    free(used);
    free(order);
    free(comp);
    free(assignment);

    return 0;
}
