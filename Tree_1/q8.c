#include <stdio.h>
#include <stdlib.h>

// Structure to cleanly hold query information
typedef struct {
    char type;
    int arg1;
    int arg2;
} Query;

// Binary Indexed Tree (Fenwick Tree) tracking array and its working size
int *bit_tree;
int bit_size;

// Add a value to the Fenwick Tree structure at a specific 1-based index
void bit_add(int idx, int delta) {
    for (; idx <= bit_size; idx += idx & -idx) {
        bit_tree[idx] += delta;
    }
}

// Prefix sum query up to a 1-based index
int bit_query_prefix(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit_tree[idx];
    }
    return sum;
}

// Range sum query between two 1-based indices [l, r]
int bit_query_range(int l, int r) {
    if (l > r) return 0;
    return bit_query_prefix(r) - bit_query_prefix(l - 1);
}

// Comparison function needed for standard qsort utility
int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// Custom implementation of lower_bound (finds first element >= val)
int lower_bound(int *arr, int size, int val) {
    int low = 0, high = size;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= val) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

// Custom implementation of upper_bound (finds first element > val)
int upper_bound(int *arr, int size, int val) {
    int low = 0, high = size;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] > val) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int main() {
    // Optimize standard I/O streams for competitive programming speeds
    setvbuf(stdout, NULL, _IOFBF, 16384);

    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    // Track dynamic memory arrays safely
    int *salaries = (int *)malloc((n + 1) * sizeof(int));
    Query *queries = (Query *)malloc(q * sizeof(Query));

    // Array to hold all seen numeric instances for ranking compression
    int max_vals = n + 2 * q;
    int *all_values = (int *)malloc(max_vals * sizeof(int));
    int val_count = 0;

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &salaries[i]);
        all_values[val_count++] = salaries[i];
    }

    for (int i = 0; i < q; ++i) {
        // Read space/newline, then token char and values
        scanf(" %c %d %d", &queries[i].type, &queries[i].arg1, &queries[i].arg2);
        if (queries[i].type == '!') {
            all_values[val_count++] = queries[i].arg2;
        } else {
            all_values[val_count++] = queries[i].arg1;
            all_values[val_count++] = queries[i].arg2;
        }
    }

    // Coordinate Compression step: Sort values array
    qsort(all_values, val_count, sizeof(int), compare_ints);

    // Deduplicate array values in-place
    int unique_count = 0;
    if (val_count > 0) {
        unique_count = 1;
        for (int i = 1; i < val_count; ++i) {
            if (all_values[i] != all_values[i - 1]) {
                all_values[unique_count++] = all_values[i];
            }
        }
    }

    // Allocate tree memory matching the exact universe of unique items
    bit_size = unique_count;
    bit_tree = (int *)calloc(bit_size + 1, sizeof(int));

    // Populate initial configuration settings into tracking structure
    for (int i = 1; i <= n; ++i) {
        int idx = lower_bound(all_values, unique_count, salaries[i]) + 1;
        bit_add(idx, 1);
    }

    // Process input requests active in problem query queue
    for (int i = 0; i < q; ++i) {
        if (queries[i].type == '!') {
            int k = queries[i].arg1;
            int x = queries[i].arg2;

            // Remove previous data state from index tree
            int old_idx = lower_bound(all_values, unique_count, salaries[k]) + 1;
            bit_add(old_idx, -1);

            // Update underlying baseline register
            salaries[k] = x;

            // Record replacement node value
            int new_idx = lower_bound(all_values, unique_count, salaries[k]) + 1;
            bit_add(new_idx, 1);
        } else {
            int a = queries[i].arg1;
            int b = queries[i].arg2;

            // Locate inclusive operational range matches inside scale array
            int l_idx = lower_bound(all_values, unique_count, a) + 1;
            int r_idx = upper_bound(all_values, unique_count, b); // index directly maps to 1-based target range

            printf("%d\n", bit_query_range(l_idx, r_idx));
        }
    }

    // Dynamic memory cleanup
    free(salaries);
    free(queries);
    free(all_values);
    free(bit_tree);

    return 0;
}
