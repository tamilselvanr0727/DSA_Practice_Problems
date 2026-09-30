#include <stdio.h>
#include <stdlib.h>

#define INF 2000000000 // A value larger than any possible array element (10^9)

// Segment tree array. Size needs to be 4 * N
int tree[800005];
int arr[200005];

// Function to build the segment tree
void build(int node, int start, int end) {
    if (start == end) {
        // Leaf node will have a single element
        tree[node] = arr[start];
        return;
    }
    
    int mid = start + (end - start) / 2;
    
    // Recurse on the left child
    build(2 * node, start, mid);
    // Recurse on the right child
    build(2 * node + 1, mid + 1, end);
    
    // Internal node will store the minimum of both children
    tree[node] = (tree[2 * node] < tree[2 * node + 1]) ? tree[2 * node] : tree[2 * node + 1];
}

// Function to query the segment tree for the minimum in range [ql, qr]
int query(int node, int start, int end, int ql, int qr) {
    // If the current segment is completely outside the query range
    if (qr < start || end < ql) {
        return INF;
    }
    
    // If the current segment is completely inside the query range
    if (ql <= start && end <= qr) {
        return tree[node];
    }
    
    // If the current segment overlaps partially with the query range
    int mid = start + (end - start) / 2;
    int left_res = query(2 * node, start, mid, ql, qr);
    int right_res = query(2 * node + 1, mid + 1, end, ql, qr);
    
    return (left_res < right_res) ? left_res : right_res;
}

int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    
    for (int i = 1; i <= n; i++) {
        if (scanf("%d", &arr[i]) != 1) return 0;
    }
    
    // Build the segment tree using 1-based indexing
    build(1, 1, n);
    
    // Process each range minimum query
    for (int i = 0; i < q; i++) {
        int a, b;
        if (scanf("%d %d", &a, &b) != 2) return 0;
        
        // Output the result of the query
        printf("%d\n", query(1, 1, n, a, b));
    }
    
    return 0;
}
