#include <stdio.h>
#include <stdlib.h>

// Function to find the maximum element in an array
long long get_max(long long *arr, int size) {
    long long max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int main() {
    int M;
    long long N;
    
    // Read M (number of rows) and N (number of fans)
    if (scanf("%d %lld", &M, &N) != 2) return 0;
    
    long long *seats = (long long *)malloc(M * sizeof(long long));
    for (int i = 0; i < M; i++) {
        if (scanf("%lld", &seats[i]) != 1) return 0;
    }
    
    // Binary Search to find the threshold price K
    long long low = 0;
    long long high = get_max(seats, M);
    long long K = high;
    
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long taken = 0;
        
        for (int i = 0; i < M; i++) {
            if (seats[i] >= mid) {
                taken += (seats[i] - mid + 1);
            }
        }
        
        if (taken >= N) {
            K = mid;       // mid is a viable threshold price
            low = mid + 1; // Try to see if we can find a higher threshold
        } else {
            high = mid - 1;
        }
    }
    
    // Calculate total revenue based on the threshold K
    long long total_revenue = 0;
    long long tickets_sold = 0;
    
    for (int i = 0; i < M; i++) {
        if (seats[i] >= K) {
            long long count = seats[i] - K + 1;
            tickets_sold += count;
            
            // Sum of arithmetic progression from K to seats[i]
            // Formula: count * (first_term + last_term) / 2
            total_revenue += (count * (seats[i] + K)) / 2;
        }
    }
    
    // If we took too many tickets due to duplicates at threshold K,
    // subtract the excess tickets evaluated at price K
    if (tickets_sold > N) {
        long long excess = tickets_sold - N;
        total_revenue -= (excess * K);
    }
    
    // Print the final maximum pounds gained
    printf("%lld\n", total_revenue);
    
    free(seats);
    return 0;
}
