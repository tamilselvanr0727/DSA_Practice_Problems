#include <stdio.h>
#include <stdlib.h>

#define MAXQ 500005

typedef struct {
    int type;
    long long val;
    int compressed_val;
} Query;

Query queries[MAXQ];
long long unique_vals[MAXQ];
int bit[MAXQ];
int unique_count = 0;

// Binary search to find the compressed coordinate index
int get_compressed_idx(long long val) {
    int low = 1, high = unique_count, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (unique_vals[mid] == val) return mid;
        if (unique_vals[mid] < val) low = mid + 1;
        else high = mid - 1;
    }
    return ans;
}

// standard comparison function for qsort
int compare_ll(const void *a, const void *b) {
    long long va = *(const long long *)a;
    long long vb = *(const long long *)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

// Fenwick Tree (BIT) Operations
void update(int idx, int val, int n) {
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] += val;
    }
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit[idx];
    }
    return sum;
}

int main() {
    long long n;
    int q;
    if (scanf("%lld %d", &n, &q) != 2) return 0;

    long long *temp_vals = (long long *)malloc(sizeof(long long) * q);
    int temp_count = 0;

    // Step 1: Read all queries and extract coordinates for compression
    for (int i = 0; i < q; i++) {
        scanf("%d %lld", &queries[i].type, &queries[i].val);
        temp_vals[temp_count++] = queries[i].val;
    }

    // Step 2: Sort and deduplicate coordinates
    qsort(temp_vals, temp_count, sizeof(long long), compare_ll);
    
    for (int i = 0; i < temp_count; i++) {
        if (i == 0 || temp_vals[i] != temp_vals[i - 1]) {
            unique_count++;
            unique_vals[unique_count] = temp_vals[i];
        }
    }
    free(temp_vals);

    // Step 3: Map original coordinates to compressed indices
    for (int i = 0; i < q; i++) {
        queries[i].compressed_val = get_compressed_idx(queries[i].val);
    }

    // Array to track if an element is already updated to avoid duplicates
    char *is_active = (char *)calloc(unique_count + 1, sizeof(char));

    // Step 4: Process queries online using the compressed structures
    for (int i = 0; i < q; i++) {
        if (queries[i].type == 1) {
            int c_idx = queries[i].compressed_val;
            if (!is_active[c_idx]) {
                is_active[c_idx] = 1;
                update(c_idx, 1, unique_count);
            }
        } else {
            int c_idx = queries[i].compressed_val;
            
            // Count total active elements before this index
            int base_prefix = query(c_idx - 1);
            
            // Binary search over the Fenwick Tree to find the smallest valid element
            int low = c_idx, high = unique_count, ans_idx = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                int current_prefix = query(mid);
                
                // If there's at least one active element between c_idx and mid
                if (current_prefix - base_prefix > 0) {
                    ans_idx = mid;
                    high = mid - 1; // Try to find an even smaller index
                } else {
                    low = mid + 1;
                }
            }

            if (ans_idx == -1) {
                printf("-1\n");
            } else {
                printf("%lld\n", unique_vals[ans_idx]);
            }
        }
    }

    free(is_active);
    return 0;
}
