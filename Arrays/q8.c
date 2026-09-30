#include <stdio.h>

int main() {
    int t;
    // Read the number of test cases
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        int n, m;
        // Read dimensions: n = rows, m = columns
        if (scanf("%d %d", &n, &m) != 2) break;

        // Using a 2D array to store the matrix (1-indexed for convenience)
        long long matrix[n + 1][m + 1];

        // Read the matrix elements from the input stream
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%lld", &matrix[i][j]);
            }
        }

        int x1, y1, x2, y2;
        // Read the top-left and bottom-right submatrix boundaries
        if (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != 4) break;

        long long submatrix_sum = 0;

        // Iterate through the specified submatrix boundaries and accumulate the sum
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                submatrix_sum += matrix[i][j];
            }
        }

        // Print the final calculated sum
        printf("%lld\n", submatrix_sum);
    }

    return 0;
}
