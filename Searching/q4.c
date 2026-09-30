#include <stdio.h>

#define MAX_R 100000

// Array to store precomputed running count of valid numbers
int prefix[MAX_R + 1];

// Function to calculate Greatest Common Divisor (Euclidean algorithm)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the sum of digits of n in base 16 (hexadecimal)
int get_hex_digit_sum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 16;
        n /= 16;
    }
    return sum;
}

// Precomputes the prefix sums for all numbers up to MAX_R
void precompute() {
    prefix[0] = 0;
    for (int i = 1; i <= MAX_R; i++) {
        int f_i = get_hex_digit_sum(i);
        
        // If GCD(X, F(X)) > 1, it's a valid integer
        if (gcd(i, f_i) > 1) {
            prefix[i] = prefix[i - 1] + 1;
        } else {
            prefix[i] = prefix[i - 1];
        }
    }
}

int main() {
    // 1. Precompute counts up to maximum possible constraint R (10^5)
    precompute();

    int t;
    // Read the total number of test cases
    if (scanf("%d", &t) != 1) return 0;

    // 2. Process each range query instantly
    while (t--) {
        int l, r;
        if (scanf("%d %d", &l, &r) == 2) {
            int result = prefix[r] - prefix[l - 1];
            printf("%d\n", result);
        }
    }

    return 0;
}
