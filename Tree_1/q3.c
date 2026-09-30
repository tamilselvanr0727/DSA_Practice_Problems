#include <stdio.h>

#define MAX_N 1005

// Global arrays to prevent stack overflow issues on large sizes
int pref[MAX_N][MAX_N];
char row[MAX_N];

int main() {
    int n, q;
    
    // Read dimensions and query count
    if (scanf("%d %d", &n, &q) != 2) return 0;
    
    // Build the 2D prefix sum array
    for (int i = 1; i <= n; i++) {
        scanf("%s", row);
        for (int j = 1; j <= n; j++) {
            int val = (row[j - 1] == '*') ? 1 : 0;
            
            // 2D Prefix Sum Preprocessing Formula
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + val;
        }
    }
    
    // Process each query in O(1) time
    for (int i = 0; i < q; i++) {
        int y1, x1, y2, x2;
        scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
        
        // 2D Subgrid sum query formula
        int ans = pref[y2][x2] - pref[y1 - 1][x2] - pref[y2][x1 - 1] + pref[y1 - 1][x1 - 1];
        
        printf("%d\n", ans);
    }
    
    return 0;
}
