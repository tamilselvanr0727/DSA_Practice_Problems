#include <stdio.h>
#include <math.h>

// Maximum possible value of an element for length up to 10^13 is around 251,189
#define MAX_VAL 255000

// Prefix sums array to store the cumulative length of the array up to element i
long long prefix_sums[MAX_VAL + 1];

void precompute() {
    long long current_total = 0;
    
    for (long long i = 1; i <= MAX_VAL; ++i) {
        // Calculate occurrences of element i: f(i) = i * floor(sqrt(i)) + ceil(i / 2.0)
        long long sq = (long long)floor(sqrt(i));
        long long cl = (long long)ceil(i / 2.0);
        
        long long count_i = i * sq + cl;
        current_total += count_i;
        prefix_sums[i] = current_total;
    }
}

// Custom binary search to find the value located at a 1-based index X
long long get_value_at_index(long long X) {
    long long low = 1, high = MAX_VAL;
    long long ans = MAX_VAL;
    
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        
        if (prefix_sums[mid] >= X) {
            ans = mid;         // Candidate solution found
            high = mid - 1;    // Look for a smaller value to find the first occurrence
        } else {
            low = mid + 1;     // Look in the upper half
        }
    }
    return ans;
}

int main() {
    // Optimize standard I/O execution speed
    precompute();
    
    int Q;
    if (scanf("%d", &Q) == 1) {
        while (Q--) {
            long long L, R;
            scanf("%lld %lld", &L, &R);
            
            long long val_L = get_value_at_index(L);
            long long val_R = get_value_at_index(R);
            
            long long distinct_elements = val_R - val_L + 1;
            printf("%lld\n", distinct_elements);
        }
    }
    return 0;
}
