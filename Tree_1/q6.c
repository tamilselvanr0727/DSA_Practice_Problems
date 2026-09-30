#include <stdio.h>
#include <stdlib.h>

#define LOG 19 // Since 2^18 = 262,144 > 200,000 (Max N)

int main() {
    int n, q;
    
    // Read total employees and queries
    if (scanf("%d %d", &n, &q) != 2) return 0;

    // Dynamically allocate a 2D matrix flattened into a 1D array: size (n + 1) * LOG
    // up[x * LOG + j] stores the (2^j)-th boss of employee x
    int *up = (int *)malloc((n + 1) * LOG * sizeof(int));
    if (up == NULL) return 1;

    // Initialize the entire lookup table with -1 (no boss)
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < LOG; j++) {
            up[i * LOG + j] = -1;
        }
    }

    // Read immediate bosses (2^0-th boss) for employees 2 to n
    for (int i = 2; i <= n; i++) {
        scanf("%d", &up[i * LOG + 0]);
    }

    // Precompute the binary lifting ancestor matrix
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            int immediate_boss = up[i * LOG + (j - 1)];
            if (immediate_boss != -1) {
                up[i * LOG + j] = up[immediate_boss * LOG + (j - 1)];
            }
        }
    }

    // Process all queries efficiently
    for (int i = 0; i < q; i++) {
        int x, k;
        scanf("%d %d", &x, &k);

        // Jump up the tree matching the bits of k
        for (int j = 0; j < LOG; j++) {
            if ((k >> j) & 1) {
                x = up[x * LOG + j];
                if (x == -1) {
                    break; // Exceeded the general director (root)
                }
            }
        }
        printf("%d\n", x);
    }

    // Clean up allocated memory
    free(up);
    return 0;
}
