#include <stdio.h>
#include <stdlib.h>

// Global tracking structure for the Fenwick Tree
int *bit_tree;
int bit_size;

// Add a value to the tree at position i
void bit_add(int i, int delta) {
    for (; i <= bit_size; i += i & -i) {
        bit_tree[i] += delta;
    }
}

// Find the index of the k-th active remaining element using Binary Lifting
int bit_find_kth(int k) {
    int idx = 0;
    // 1 << 18 is 262,144 (the smallest power of 2 greater than max N = 200,000)
    for (int i = 1 << 18; i > 0; i >>= 1) {
        if (idx + i <= bit_size && bit_tree[idx + i] < k) {
            idx += i;
            k -= bit_tree[idx];
        }
    }
    return idx + 1;
}

int main(void) {
    int n;
    // Read list size
    if (scanf("%d", &n) != 1) return 0;

    // Dynamically allocate memory for 1-based index arrays
    int *x = (int *)malloc((n + 1) * sizeof(int));
    bit_tree = (int *)calloc((n + 1), sizeof(int));
    bit_size = n;

    // Read the initial array elements
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x[i]);
    }

    // Initialize the Fenwick tree: every initial index holds 1 active item
    for (int i = 1; i <= n; i++) {
        bit_add(i, 1);
    }

    // Process each removal operation
    for (int i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);

        // Find the actual original position of the current p-th element
        int actual_idx = bit_find_kth(p);

        // Print the element value
        printf("%d%c", x[actual_idx], (i == n - 1) ? '\n' : ' ');

        // Deactivate the element at actual_idx by adding -1
        bit_add(actual_idx, -1);
    }

    // Free dynamically allocated heap memory
    free(x);
    free(bit_tree);

    return 0;
}
