#include <stdio.h>

int main() {
    int n;
    // Read the total number of rectangles
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    int silver_count = 0;

    for (int i = 0; i < n; i++) {
        long long w, h;
        // Read width and height for each rectangle
        if (scanf("%lld %lld", &w, &h) != 2) {
            break;
        }

        // Determine the larger and smaller sides to safely handle orientation
        long long side1 = (w > h) ? w : h;
        long long side2 = (w < h) ? w : h;

        // Check if 1.6 <= side1 / side2 <= 1.7 using integer cross-multiplication
        // 16 * side2 <= 10 * side1 <= 17 * side2
        if (16 * side2 <= 10 * side1 && 10 * side1 <= 17 * side2) {
            silver_count++;
        }
    }

    // Print the final count
    printf("%d\n", silver_count);

    return 0;
}
