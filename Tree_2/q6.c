#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

// Global data arrays allocated statically to avoid stack overhead
static long long arr[MAXN];

typedef struct {
    long long sum;
    long long lazy_d;
    long long lazy_c;
} SegmentNode;

static SegmentNode tree[4 * MAXN];

/* 
 * Fast I/O Implementation for integers
 * Dramatically speeds up reading input compared to standard scanf
 */
static inline int read_int(void) {
    int c = getchar();
    while (c <= 32) {
        if (c == EOF) return 0;
        c = getchar();
    }
    int res = 0;
    while (c > 32) {
        res = res * 10 + (c - '0');
        c = getchar();
    }
    return res;
}

static inline long long read_long(void) {
    int c = getchar();
    while (c <= 32) {
        if (c == EOF) return 0;
        c = getchar();
    }
    long long res = 0;
    while (c > 32) {
        res = res * 10 + (c - '0');
        c = getchar();
    }
    return res;
}

/* 
 * Computes the sum of sequence elements: L + (L+1) + ... + R
 */
static inline long long get_index_sum(long long L, long long R) {
    return (L + R) * (R - L + 1) / 2;
}

/* 
 * Builds the initial Segment Tree from the input array
 */
void build_tree(int node, int L, int R) {
    tree[node].lazy_d = 0;
    tree[node].lazy_c = 0;
    if (L == R) {
        tree[node].sum = arr[L];
        return;
    }
    int mid = L + (R - L) / 2;
    build_tree(2 * node, L, mid);
    build_tree(2 * node + 1, mid + 1, R);
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
}

/* 
 * Pushes the pending updates from a parent node down to its two children
 */
void push_lazy(int node, int L, int R) {
    if (tree[node].lazy_d == 0 && tree[node].lazy_c == 0) {
        return;
    }

    int mid = L + (R - L) / 2;
    int left_child = 2 * node;
    int right_child = 2 * node + 1;

    // Apply linear functions to the left child
    tree[left_child].lazy_d += tree[node].lazy_d;
    tree[left_child].lazy_c += tree[node].lazy_c;
    tree[left_child].sum += tree[node].lazy_d * get_index_sum(L, mid) + tree[node].lazy_c * (mid - L + 1);

    // Apply linear functions to the right child
    tree[right_child].lazy_d += tree[node].lazy_d;
    tree[right_child].lazy_c += tree[node].lazy_c;
    tree[right_child].sum += tree[node].lazy_d * get_index_sum(mid + 1, R) + tree[node].lazy_c * (R - mid);

    // Reset parent tags
    tree[node].lazy_d = 0;
    tree[node].lazy_c = 0;
}

/* 
 * Updates the range [ql, qr] with an arithmetic progression starting at 1
 */
void update_range(int node, int L, int R, int ql, int qr) {
    if (ql <= L && R <= qr) {
        long long d = 1;
        long long c = 1 - ql;
        tree[node].lazy_d += d;
        tree[node].lazy_c += c;
        tree[node].sum += d * get_index_sum(L, R) + c * (R - L + 1);
        return;
    }
    push_lazy(node, L, R);
    int mid = L + (R - L) / 2;
    if (ql <= mid) {
        update_range(2 * node, L, mid, ql, qr);
    }
    if (qr > mid) {
        update_range(2 * node + 1, mid + 1, R, ql, qr);
    }
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
}

/* 
 * Queries the sum of elements in the range [ql, qr]
 */
long long query_range(int node, int L, int R, int ql, int qr) {
    if (ql <= L && R <= qr) {
        return tree[node].sum;
    }
    push_lazy(node, L, R);
    int mid = L + (R - L) / 2;
    long long total_sum = 0;
    if (ql <= mid) {
        total_sum += query_range(2 * node, L, mid, ql, qr);
    }
    if (qr > mid) {
        total_sum += query_range(2 * node + 1, mid + 1, R, ql, qr);
    }
    return total_sum;
}

int main(void) {
    int n = read_int();
    int q = read_int();
    if (n == 0) return 0;

    for (int i = 1; i <= n; i++) {
        arr[i] = read_long();
    }

    build_tree(1, 1, n);

    for (int i = 0; i < q; i++) {
        int type = read_int();
        int a = read_int();
        int b = read_int();
        
        if (type == 1) {
            update_range(1, 1, n, a, b);
        } else {
            printf("%lld\n", query_range(1, 1, n, a, b));
        }
    }

    return 0;
}
