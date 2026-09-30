#include <stdio.h>
#include <stdlib.h>

void solve() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return;

    // Allocate 1D arrays dynamically to handle memory for dynamic grid sizes safely.
    // We add +1 to rows and columns to naturally accommodate 1-based indexing.
    int rows = n + 1;
    int cols = m + 1;
    
    long long *grid = (long long *)calloc(rows * cols, sizeof(long long));
    long long *prefix = (long long *)calloc(rows * cols, sizeof(long long));

    // Read the flattened grid input matrix C[N][M]
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &grid[i * cols + j]);
        }
    }

    // Precompute the 2D Prefix Sum matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            prefix[i * cols + j] = grid[i * cols + j] 
                                 + prefix[(i - 1) * cols + j] 
                                 + prefix[i * cols + (j - 1)] 
                                 - prefix[(i - 1) * cols + (j - 1)];
        }
    }

    // Read the submatrix boundary coordinates
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    // Calculate the target submatrix sum in O(1) time
    long long total_sum = prefix[x2 * cols + y2] 
                        - prefix[(x1 - 1) * cols + y2] 
                        - prefix[x2 * cols + (y1 - 1)] 
                        + prefix[(x1 - 1) * cols + (y1 - 1)];

    // Print result
    printf("%lld\n", total_sum);

    // Dynamic memory cleanup
    free(grid);
    free(prefix);
}

int main() {
    // Optimize standard C I/O performance limits
    setvbuf(stdout, NULL, _IOFBF, 16384);
    
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
