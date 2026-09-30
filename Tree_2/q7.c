#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL 100005

// Global frequency array to track occurrences of each element
// count[x] = 0: element not present
// count[x] = 1: element present in increasing part
// count[x] = 2: element present in both increasing and decreasing parts
int count[MAX_VAL];

int main() {
    // Fast I/O optimization
    setvbuf(stdout, NULL, _IOFBF, 16384);

    int n;
    if (scanf("%d", &n) != 1) return 0;

    int current_max = 0;
    int current_size = 0;

    // Read initial elements of the valid B-sequence
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        count[x]++;
        current_size++;
        if (x > current_max) {
            current_max = x;
        }
    }

    int q;
    if (scanf("%d", &q) != 1) return 0;

    while (q--) {
        int val;
        scanf("%d", &val);

        if (val > current_max) {
            // val becomes the new maximum element.
            // Even if it was present in the sequence before, it now transitions 
            // entirely to the increasing part, meaning its maximum allowed count is 1.
            if (count[val] == 0) {
                current_size++;
            } else if (count[val] == 2) {
                // If it was present twice, it can now only be present once as the peak
                current_size--; 
            }
            count[val] = 1;
            current_max = val;
        } 
        else if (val < current_max) {
            // Can be placed in increasing part if not already there
            if (count[val] == 0) {
                count[val] = 1;
                current_size++;
            } 
            // If already in increasing part, can be placed in decreasing part
            else if (count[val] == 1) {
                count[val] = 2;
                current_size++;
            }
            // If count[val] == 2, it is already filled in both parts, so do nothing
        }
        // If val == current_max, it's already the peak and cannot be inserted again

        printf("%d\n", current_size);
    }

    // Print the final B-sequence
    int first = 1;

    // Part 1: Print strictly increasing elements (all elements present at least once)
    for (int i = 1; i <= current_max; i++) {
        if (count[i] >= 1) {
            if (!first) printf(" ");
            printf("%d", i);
            first = 0;
        }
    }

    // Part 2: Print strictly decreasing elements (elements present exactly twice)
    // Note: The peak (current_max) can never have count == 2, so it naturally terminates correctly.
    for (int i = current_max - 1; i >= 1; i--) {
        if (count[i] == 2) {
            printf(" %d", i);
        }
    }
    printf("\n");

    return 0;
}
