#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort to sort in ascending order
int compare_asc(const void *a, const void *b) {
    long long val_a = *(const long long *)a;
    long long val_b = *(const long long *)b;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

void solve() {
    int n;
    if (scanf("%d", &n) != 1) return;
    
    // Using long long to prevent potential overflow during multiplication
    long long *a = (long long *)malloc(n * sizeof(long long));
    long long *b = (long long *)malloc(n * sizeof(long long));
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }
    
    // Sort both arrays in ascending order
    qsort(a, n, sizeof(long long), compare_asc);
    qsort(b, n, sizeof(long long), compare_asc);
    
    long long min_product_sum = 0;
    for (int i = 0; i < n; i++) {
        // Multiply the smallest remaining element in 'a' 
        // with the largest remaining element in 'b' (from the end)
        min_product_sum += a[i] * b[n - 1 - i];
    }
    
    printf("%lld\n", min_product_sum);
    
    // Free allocated memory
    free(a);
    free(b);
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
