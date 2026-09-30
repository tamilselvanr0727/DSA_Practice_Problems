#include <stdio.h>
#include <string.h>

void solve() {
    int m;
    scanf("%d", &m);
    
    // Allocate space for the string (M max is 100, so 105 is safe)
    char s[105];
    scanf("%s", s);
    
    // Calculate the window size k = ceil(M / 2.0)
    // Integer arithmetic trick for ceil(A/B) is (A + B - 1) / B
    int k = (m + 1) / 2;
    
    int current_window_sum = 0;
    
    // Calculate the sum of the first window
    for (int i = 0; i < k; i++) {
        current_window_sum += (s[i] - '0'); // Convert char digit to integer
    }
    
    int max_beauty = current_window_sum;
    
    // Slide the window across the string
    for (int i = k; i < m; i++) {
        // Add the incoming character and subtract the outgoing character
        current_window_sum += (s[i] - '0') - (s[i - k] - '0');
        
        if (current_window_sum > max_beauty) {
            max_beauty = current_window_sum;
        }
    }
    
    printf("%d\n", max_beauty);
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
