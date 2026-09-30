#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort to sort in ascending order
int compare(const void *a, const void *b) {
    long long val_a = *(const long long *)a;
    long long val_b = *(const long long *)b;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

void solve() {
    int n;
    if (scanf("%d", &n) != 1) return;

    // Use long long since container[i][j] <= 10^9 and n <= 100
    // Total sum can exceed standard 32-bit integer limits (up to 10^11)
    long long *row_sums = (long long *)calloc(n, sizeof(long long));
    long long *col_sums = (long long *)calloc(n, sizeof(long long));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long val;
            scanf("%lld", &val);
            row_sums[i] += val;
            col_sums[j] += val;
        }
    }

    // Sort both sum arrays to check for a perfect match
    qsort(row_sums, n, sizeof(long long), compare);
    qsort(col_sums, n, sizeof(long long), compare);

    // Compare sorted configurations
    int possible = 1;
    for (int i = 0; i < n; i++) {
        if (row_sums[i] != col_sums[i]) {
            possible = 0;
            break;
        }
    }

    if (possible) {
        printf("Possible\n");
    } else {
        printf("Impossible\n");
    }

    // Free dynamically allocated arrays
    free(row_sums);
    free(col_sums);
}

int main() {
    int q;
    if (scanf("%d", &q) == 1) {
        while (q--) {
            solve();
        }
    }
    return 0;
}
