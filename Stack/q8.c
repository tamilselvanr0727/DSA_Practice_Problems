#include <stdio.h>
#include <stdlib.h>

// Function to find the maximum stamina required from any building
long long solve_max_stamina(int n, const long long* heights) {
    // nge_index tracks the next greater element index
    int* nge_index = (int*)malloc(n * sizeof(int));
    // dp array stores the accumulated XOR values for each building path
    long long* dp = (long long*)malloc(n * sizeof(long long));
    // stack array to hold indices for the monotonic stack structure
    int* stack = (int*)malloc(n * sizeof(int));
    
    int stack_top = -1;
    long long max_stamina = 0;
    
    // Process buildings from right to left
    for (int i = n - 1; i >= 0; i--) {
        // Pop elements smaller than or equal to current building height
        while (stack_top >= 0 && heights[stack[stack_top]] <= heights[i]) {
            stack_top--;
        }
        
        // If stack is not empty, the top element is the next higher building
        if (stack_top >= 0) {
            int next_greater = stack[stack_top];
            nge_index[i] = next_greater;
            dp[i] = heights[i] ^ dp[next_greater]; // Compute path XOR value
        } else {
            nge_index[i] = -1; // No higher building found to the right
            dp[i] = heights[i];
        }
        
        // Push the current building index onto the stack
        stack[++stack_top] = i;
        
        // Maintain the global maximum value found across all passes
        if (dp[i] > max_stamina) {
            max_stamina = dp[i];
        }
    }
    
    // Free allocated dynamic heap memory
    free(nge_index);
    free(dp);
    free(stack);
    
    return max_stamina;
}

int main() {
    int n;
    
    // Fast I/O configuration
    if (scanf("%d", &n) != 1) return 0;
    
    long long* heights = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &heights[i]) != 1) break;
    }
    
    long long result = solve_max_stamina(n, heights);
    printf("%lld\n", result);
    
    free(heights);
    return 0;
}
