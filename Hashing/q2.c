#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int t;
    // Read the total number of test cases
    if (scanf("%d", &t) != 1) {
        return 0;
    }
    
    // Golden ratio constant: (1 + sqrt(5)) / 2
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    
    while (t--) {
        int a, b;
        if (scanf("%d %d", &a, &b) != 2) {
            break;
        }
        
        // n is the absolute difference between coordinates
        int n = abs(a - b);
        
        // Find the smaller of the two coordinates
        int min_val = (a < b) ? a : b;
        
        // Check if it matches the losing position formula
        // Using a small epsilon offset to prevent floating-point inaccuracies
        if (min_val == (int)floor(n * phi + 1e-9)) {
            printf("sami\n");
        } else {
            printf("canthi\n");
        }
    }
    
    return 0;
}
