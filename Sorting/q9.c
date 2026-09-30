#include <stdio.h>
#include <string.h>

#define MAX_P 1501
#define MAX_K 31

// Macro to find the maximum of two values
#define MAX(a, b) ((a) > (b) ? (a) : (b))
// Macro to find the minimum of two values
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void solve() {
    int N, K, P;
    if (scanf("%d %d %d", &N, &K, &P) != 3) return;

    // dp[j] stores the max attractive value picking exactly j leaves
    int dp[MAX_P];
    memset(dp, 0, sizeof(dp));

    // Temporary array to store transitions for the current stack
    int next_dp[MAX_P];

    for (int i = 0; i < N; i++) {
        int stack[MAX_K];
        int pref[MAX_K] = {0};

        // Read stack values and compute prefix sums simultaneously
        for (int j = 1; j <= K; j++) {
            scanf("%d", &stack[j]);
            pref[j] = pref[j - 1] + stack[j];
        }

        // Initialize the temporary DP array for this stack iteration
        memset(next_dp, 0, sizeof(next_dp));

        // Update DP table
        for (int j = 0; j <= P; j++) {
            int limit = MIN(K, j);
            for (int x = 0; x <= limit; x++) {
                next_dp[j] = MAX(next_dp[j], dp[j - x] + pref[x]);
            }
        }

        // Copy back to the main dp table for the next stack
        memcpy(dp, next_dp, sizeof(dp));
    }

    printf("%d\n", dp[P]);
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
