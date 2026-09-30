#include <stdio.h>
#include <stdlib.h>

// Comparison function to sort in ascending order (for girls)
int compare_asc(const void *a, const void *b) {
    int val_a = *(const int *)a;
    int val_b = *(const int *)b;
    return (val_a > val_b) - (val_a < val_b);
}

// Comparison function to sort in descending order (for boys)
int compare_desc(const void *a, const void *b) {
    int val_a = *(const int *)a;
    int val_b = *(const int *)b;
    return (val_b > val_a) - (val_b < val_a);
}

void solve() {
    int t;
    if (scanf("%d", &t) != 1) return;

    // Static buffers based on max constraint N <= 10^4
    int girls[10005];
    int boys[10005];

    while (t--) {
        int n;
        if (scanf("%d", &n) != 1) break;

        // Read girls' heights
        for (int i = 0; i < n; i++) {
            scanf("%d", &girls[i]);
        }

        // Read boys' heights
        for (int i = 0; i < n; i++) {
            scanf("%d", &boys[i]);
        }

        // Sort girls in ascending order
        qsort(girls, n, sizeof(int), compare_asc);

        // Sort boys in descending order
        qsort(boys, n, sizeof(int), compare_desc);

        // Count the ideal pairs
        int ideal_pairs = 0;
        for (int i = 0; i < n; i++) {
            int g = girls[i];
            int b = boys[i];
            
            // Check if one modulo the other is 0
            if (g % b == 0 || b % g == 0) {
                ideal_pairs++;
            }
        }

        // Print the result for the current test case
        printf("%d\n", ideal_pairs);
    }
}

int main() {
    solve();
    return 0;
}

