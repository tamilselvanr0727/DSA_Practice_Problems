#include <stdio.h>

void solve() {
    int T;
    // Read the total number of test cases
    if (scanf("%d", &T) != 1) return;

    while (T--) {
        int N;
        long long D;
        // Read N (number of trains) and D (deadline day)
        scanf("%d %lld", &N, &D);

        long long X[1005];
        for (int i = 0; i < N; i++) {
            scanf("%lld", &X[i]);
        }

        // Work backwards from the destination day D
        long long current_deadline = D;
        for (int i = N - 1; i >= 0; i--) {
            // Find the largest multiple of X[i] <= current_deadline
            current_deadline = (current_deadline / X[i]) * X[i];
        }

        // Print the latest day he can take the first train
        printf("%lld\n", current_deadline);
    }
}

int main() {
    solve();
    return 0;
}
