#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

// Tree Representation
typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_cnt = 0;
int degree[MAXN];
int parent_node[MAXN];
int bfs_order[MAXN], bfs_cnt = 0;

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
    degree[u]++;
}

// Map structure for Suffix Automaton transitions
typedef struct MapNode {
    int key;
    int val;
    struct MapNode* next;
} MapNode;

// Suffix Automaton node structures
typedef struct {
    int len;
    int link;
    MapNode* ch;
} SAMState;

SAMState sam[MAXN * 2];
int sam_sz = 1;

void map_insert(int state, int key, int val) {
    MapNode* node = (MapNode*)malloc(sizeof(MapNode));
    node->key = key;
    node->val = val;
    node->next = sam[state].ch;
    sam[state].ch = node;
}

int map_find(int state, int key) {
    MapNode* curr = sam[state].ch;
    while (curr != NULL) {
        if (curr->key == key) return curr->val;
        curr = curr->next;
    }
    return 0;
}

// Generalized SAM Insertion logic
int sam_extend(int c, int last) {
    int cur = map_find(last, c);
    if (cur != 0) {
        if (sam[last].len + 1 == sam[cur].len) {
            return cur;
        }
        int clone = ++sam_sz;
        sam[clone].len = sam[last].len + 1;
        
        // Deep copy the map transactions
        sam[clone].ch = NULL;
        MapNode* curr = sam[cur].ch;
        while (curr != NULL) {
            map_insert(clone, curr->key, curr->val);
            curr = curr->next;
        }
        
        sam[clone].link = sam[cur].link;
        while (last != 0 && map_find(last, c) == cur) {
            // Update reference in the map
            MapNode* m = sam[last].ch;
            while (m != NULL) {
                if (m->key == c) { m->val = clone; break; }
                m = m->next;
            }
            last = sam[last].link;
        }
        sam[cur].link = clone;
        return clone;
    }

    cur = ++sam_sz;
    sam[cur].len = sam[last].len + 1;
    sam[cur].ch = NULL;

    while (last != 0 && map_find(last, c) == 0) {
        map_insert(last, c, cur);
        last = sam[last].link;
    }
    if (last == 0) {
        sam[cur].link = 1;
    } else {
        int q = map_find(last, c);
        if (sam[last].len + 1 == sam[q].len) {
            sam[cur].link = q;
        } else {
            int clone = ++sam_sz;
            sam[clone].len = sam[last].len + 1;
            
            sam[clone].ch = NULL;
            MapNode* curr = sam[q].ch;
            while (curr != NULL) {
                map_insert(clone, curr->key, curr->val);
                curr = curr->next;
            }
            
            sam[clone].link = sam[q].link;
            while (last != 0 && map_find(last, c) == q) {
                MapNode* m = sam[last].ch;
                while (m != NULL) {
                    if (m->key == c) { m->val = clone; break; }
                    m = m->next;
                }
                last = sam[last].link;
            }
            sam[q].link = sam[cur].link = clone;
        }
    }
    return cur;
}

// Queue for BFS traversal
int queue[MAXN];
int front = 0, rear = 0;
int last_pos[MAXN];

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    memset(head, -1, sizeof(head));
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            add_edge(u, v);
            add_edge(v, u);
        }
    }

    // Initialize root state
    sam[1].len = 0;
    sam[1].link = 0;
    sam[1].ch = NULL;
    last_pos[1] = 1;

    // Traverse the tree in BFS order from Root (1)
    queue[rear++] = 1;
    parent_node[1] = 0;

    while (front < rear) {
        int u = queue[front++];
        bfs_order[bfs_cnt++] = u;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            if (v != parent_node[u]) {
                parent_node[v] = u;
                queue[rear++] = v;
            }
        }
    }

    // Build Generalized SAM sequentially down the tree levels
    for (int i = 0; i < n; i++) {
        int u = bfs_order[i];
        if (u != 1) {
            int p = parent_node[u];
            last_pos[u] = sam_extend(degree[u], last_pos[p]);
        } else {
            last_pos[1] = sam_extend(degree[1], 1);
        }
    }

    // Calculate sum of distinct substrings (trips)
    long long total_trips = 0;
    for (int i = 2; i <= sam_sz; i++) {
        total_trips += (sam[i].len - sam[sam[i].link].len);
    }

    printf("%lld\n", total_trips);

    // Free memory allocations for transitions
    for(int i = 1; i <= sam_sz; i++){
        MapNode* curr = sam[i].ch;
        while(curr != NULL){
            MapNode* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }

    return 0;
}
