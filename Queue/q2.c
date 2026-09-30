#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
// Structure to hold data for each node in the Segment Tree
typedef struct {
    int max_len;
    int prefix_len;
    int suffix_len;
    char left_char;
    char right_char;
    int total_len; // Length of the interval covered by this node
} Node;

Node tree[4 * MAXN];
char s[MAXN];
// Helper function to find the maximum of two integers
int max1(int a, int b){
    return (a > b) ? a : b;
}

// Merge two child nodes into a parent node
Node merge_nodes(Node left, Node right) {
    Node parent;
    parent.total_len = left.total_len + right.total_len;
    parent.left_char = left.left_char;
    parent.right_char = right.right_char;

    // Default prefix and suffix lengths
    parent.prefix_len = left.prefix_len;
    parent.suffix_len = right.suffix_len;
    // Base maximum length from either child
    parent.max_len = max1(left.max_len, right.max_len);

    // If the boundary characters match, we can merge across the split
    if (left.right_char == right.left_char) {
        int mid_merge = left.suffix_len + right.prefix_len;
        parent.max_len = max1(parent.max_len, mid_merge);

        // Adjust prefix if the entire left node was a single identical block
        if (left.prefix_len == left.total_len) {
            parent.prefix_len = left.total_len + right.prefix_len;
        }
        // Adjust suffix if the entire right node was a single identical block
        if (right.suffix_len == right.total_len) {
            parent.suffix_len = right.total_len + left.suffix_len;
        }
    }

    return parent;
}

// Build the segment tree initially
void build(int node, int start, int end) {
    if (start == end) {
        tree[node].max_len = 1;
        tree[node].prefix_len = 1;
        tree[node].suffix_len = 1;
        tree[node].left_char = s[start];
        tree[node].right_char = s[start];
        tree[node].total_len = 1;
        return;
    }

    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

// Update a specific index in the segment tree when a bit is inverted
void update(int node, int start, int end, int idx) {
    if (start == end) {
        // Flip the bit character
        s[idx] = (s[idx] == '0') ? '1' : '0';
        tree[node].left_char = s[idx];
        tree[node].right_char = s[idx];
        return;
    }

    int mid = (start + end) / 2;
    if (idx <= mid) {
        update(2 * node, start, mid, idx);
    } else {
        update(2 * node + 1, mid + 1, end, idx);
    }
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

int main() {
    // Read input string
    if (scanf("%s", s) != 1) return 0;
    int n = strlen(s);

    int m;
    if (scanf("%d", &m) != 1) return 0;

    int *queries = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &queries[i]);
    }

    // Build the initial tree structures (using 0-indexed values internally)
    build(1, 0, n - 1);

    // Process updates
    for (int i = 0; i < m; i++) {
        int idx = queries[i] - 1; // Convert 1-based query index to 0-based
        update(1, 0, n - 1, idx);
        printf("%d", tree[1].max_len);
        if (i < m - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(queries);
    return 0;
}
