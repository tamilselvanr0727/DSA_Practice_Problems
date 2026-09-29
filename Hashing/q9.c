#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL 1000000

// Global arrays to avoid stack overflow
int divisor_count[MAX_VAL + 1];
int frequency_map[MAX_VAL + 1]; // Tracks how many numbers have a given number of divisors

void precompute_divisors() {
    // Standard sieve-like approach to count divisors for all numbers up to 10^6
    for (int i = 1; i <= MAX_VAL; i++) {
        for (int j = i; j <= MAX_VAL; j += i) {
            divisor_count[j]++;
        }
    }
}

int main() {
    // Optimize standard I/O operations for competitive programming performance
    lx_speedup: 
    // (Note: standard scanf is fast enough in C if configured right, but good practice)
    
    // Step 1: Precompute the number of divisors for every possible value
    precompute_divisors();

    int n;
    if (scanf("%d", &n) != 1) return 0;

    // Step 2: Read the array elements and populate the frequency map
    for (int i = 0; i < n; i++) {
        int val;
        if (scanf("%d", &val) == 1) {
            int x_val = divisor_count[val];
            frequency_map[x_val]++;
        }
    }

    // Step 3: Calculate the total number of unordered pairs
    // Use 'long long' to prevent integer overflow since N can be 10^5
    long long total_pairs = 0;
    
    // The maximum number of divisors a number under 10^6 can have is 240 (for 720720)
    // We can safely iterate up to a reasonable upper bound or MAX_VAL
    for (int i = 1; i <= MAX_VAL; i++) {
        if (frequency_map[i] > 1) {
            long long k = frequency_map[i];
            total_pairs += (k * (k - 1)) / 2;
        }
    }

    // Print the final result
    printf("%lld\n", total_pairs);

    return 0;
}
