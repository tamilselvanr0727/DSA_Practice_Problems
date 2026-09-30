#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort to sort in ascending order
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        int n, m;
        if (scanf("%d %d", &n, &m) != 2) break;

        int *a = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        // Sort the prices to bring the most negative values to the front
        qsort(a, n, sizeof(int), compare);

        int earnings = 0;
        int count = 0;

        // Collect at most m laptops, only if they have a negative price
        for (int i = 0; i < n; i++) {
            if (a[i] < 0 && count < m) {
                earnings += -a[i]; // Add the positive cash received
                count++;
            } else {
                break; // Since it's sorted, no more negative values exist
            }
        }

        printf("%d\n", earnings);
        free(a);
    }

    return 0;
}
