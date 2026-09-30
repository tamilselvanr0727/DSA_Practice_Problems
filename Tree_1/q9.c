#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

// DSU Structure
typedef struct {
    int parent[MAXN];
    int rank[MAXN];
} DSU;

void initDSU(DSU *dsu, int n) {
    for (int i = 1; i <= n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
}

int findSet(DSU *dsu, int i) {
    if (dsu->parent[i] == i)
        return i;
    return dsu->parent[i] = findSet(dsu, dsu->parent[i]); // Path compression
}

int unionSets(DSU *dsu, int i, int j) {
    int rootI = findSet(dsu, i);
    int rootJ = findSet(dsu, j);
    if (rootI != rootJ) {
        if (dsu->rank[rootI] < dsu->rank[rootJ]) {
            dsu->parent[rootI] = rootJ;
        } else if (dsu->rank[rootI] > dsu->rank[rootJ]) {
            dsu->parent[rootJ] = rootI;
        } else {
            dsu->parent[rootJ] = rootI;
            dsu->rank[rootI]++;
        }
        return 1; // Successfully unioned
    }
    return 0; // Already in the same set
}

// Structure to store the edges added
typedef struct {
    int u, v;
} Edge;

int main() {
    int n, m1, m2;
    if (scanf("%d %d %d", &n, &m1, &m2) != 3) return 0;

    DSU mohana, john;
    initDSU(&mohana, n);
    initDSU(&john, n);

    // Read Mohana's initial edges
    for (int i = 0; i < m1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unionSets(&mohana, u, v);
    }

    // Read John's initial edges
    for (int i = 0; i < m2; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unionSets(&john, u, v);
    }

    // Allocate memory to track added edges
    Edge *addedEdges = (Edge *)malloc(sizeof(Edge) * n);
    int edgeCount = 0;

    // Greedily try to add edges between all pairs
    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            // Check if adding (u, v) creates a cycle in either forest
            if (findSet(&mohana, u) != findSet(&mohana, v) &&
                findSet(&john, u) != findSet(&john, v)) {
                
                unionSets(&mohana, u, v);
                unionSets(&john, u, v);
                
                addedEdges[edgeCount].u = u;
                addedEdges[edgeCount].v = v;
                edgeCount++;
            }
        }
    }

    // Print total count of added edges
    printf("%d\n", edgeCount);
    
    // Print each added edge
    for (int i = 0; i < edgeCount; i++) {
        printf("%d %d\n", addedEdges[i].u, addedEdges[i].v);
    }

    free(addedEdges);
    return 0;
}
