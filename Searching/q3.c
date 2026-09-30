#include <stdio.h>
#include <stdlib.h>

// Macros for fast minimum and maximum operations
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void solve() {
    int R, C, L;
    if (scanf("%d %d %d", &R, &C, &L) != 3) return;

    // Dynamically allocate a 2D array for the matrix grid
    int **M = (int **)malloc(R * sizeof(int *));
    for (int i = 0; i < R; ++i) {
        M[i] = (int *)malloc(C * sizeof(int));
        for (int j = 0; j < C; ++j) {
            scanf("%d", &M[i][j]);
        }
    }

    // Allocate tracking arrays for the minimum and maximum of each row
    int *row_min = (int *)malloc(R * sizeof(int));
    int *row_max = (int *)malloc(R * sizeof(int));

    int max_area = 0;

    // Iterate over all possible starting columns
    for (int c1 = 0; c1 < C; ++c1) {
        // Initialize the tracking values for each row at column c1
        for (int r = 0; r < R; ++r) {
            row_min[r] = M[r][c1];
            row_max[r] = M[r][c1];
        }

        // Expand the right boundary column (c2)
        for (int c2 = c1; c2 < C; ++c2) {
            int width = c2 - c1 + 1;
            int current_consecutive = 0;
            int max_consecutive = 0;

            for (int r = 0; r < R; ++r) {
                // Update running min and max for row r dynamically
                row_min[r] = MIN(row_min[r], M[r][c2]);
                row_max[r] = MAX(row_max[r], M[r][c2]);

                // Check if the current row satisfies the thinness threshold constraint
                if (row_max[r] - row_min[r] <= L) {
                    current_consecutive++;
                    max_consecutive = MAX(max_consecutive, current_consecutive);
                } else {
                    current_consecutive = 0;
                }
            }

            int current_area = width * max_consecutive;
            max_area = MAX(max_area, current_area);
        }
    }

    // Output the result for the current test case
    printf("%d\n", max_area);

    // Free all allocated memory blocks
    free(row_min);
    free(row_max);
    for (int i = 0; i < R; ++i) {
        free(M[i]);
    }
    free(M);
}

int main() {
    int T;
    if (scanf("%d", &T) == 1) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
