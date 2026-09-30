#include <stdio.h>

int main() {
    int r, c;
    
    // Read the number of rows and columns
    if (scanf("%d %d", &r, &c) != 2) {
        return 0;
    }

    // Mandatory keywords: Declaring the matrices using Variable Length Arrays (VLA)
    int arr[r][c];
    int arrTemp[r][c];

    // Read the matrix input and initialize the temporary matrix
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &arr[i][j]);
            arrTemp[i][j] = arr[i][j];
        }
    }

    // Mandatory keyword: Outer loop tracker variables
    int m, n;
    
    // Process the matrix
    for(m=0;m<r;m++) {
        for (n = 0; n < c; n++) {
            // If the original cell contains a 1
            if (arr[m][n] == 1) {
                // Set all cells in the m-th row to 1
                for (int j = 0; j < c; j++) {
                    arrTemp[m][j] = 1;
                }
                // Set all cells in the n-th column to 1
                for (int i = 0; i < r; i++) {
                    arrTemp[i][n] = 1;
                }
            }
        }
    }

    // Print the final modified matrix
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d", arrTemp[i][j]);
            if (j < c - 1) {
                printf(" "); // Space-separated columns
            }
        }
        printf("\n"); // Newline after each row
    }

    return 0;
}
