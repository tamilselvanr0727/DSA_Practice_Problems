#include <stdio.h>
void solve() {
    int t;
    // Read the number of test cases
    if (scanf("%d", &t) != 1) return;
    while (t--) {
        int n, k;
        // Read N (number of sub-tracks) and K (initial capacity)
        if (scanf("%d %d", &n, &k) != 2) break;
        int max_dist = 0;
        for (int i = 0; i < n; i++) {
            int current_dist;
            if (scanf("%d", &current_dist) == 1) {
                // Track the maximum sub-track distance
                if (current_dist > max_dist) {
                    max_dist = current_dist;
                }
            }
        }
        // Determine the minimum required extra petrol
        if (max_dist <= k) {
            printf("-1\n");
        } else {
            printf("%d\n", max_dist - k);
        }
    }
}
int main() {
    solve();
    return 0;
}
