#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 2000

typedef struct {
    long long xl;
    long long xr;
} Street;

// Comparison function to sort streets by left boundary (and right boundary as a tie-breaker)
int compare_streets(const void *a, const void *b) {
    Street *s1 = (Street *)a;
    Street *s2 = (Street *)b;
    if (s1->xl < s2->xl) return -1;
    if (s1->xl > s2->xl) return 1;
    if (s1->xr < s2->xr) return -1;
    if (s1->xr > s2->xr) return 1;
    return 0;
}

// Helper to remove duplicate candidate values to avoid redundant checks
int unique_candidates(long long arr[], int n) {
    if (n == 0) return 0;
    
    // Sort array to put duplicates next to each other
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                long long temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    
    int unique_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[unique_idx]) {
            unique_idx++;
            arr[unique_idx] = arr[i];
        }
    }
    return unique_idx + 1;
}

void solve_test_case() {
    int N;
    long long L;
    if (scanf("%d %lld", &N, &L) != 2) return;

    Street streets[MAX_N];
    long long candidates[MAX_N * 2];
    int cand_count = 0;

    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &streets[i].xl, &streets[i].xr);
        
        // Populate candidate starting positions for the valid segment [A, A + L]
        candidates[cand_count++] = streets[i].xl;
        candidates[cand_count++] = streets[i].xr - L;
    }

    cand_count = unique_candidates(candidates, cand_count);
    bool possible = false;

    // Filter array to hold intervals valid for a given candidate
    Street filtered[MAX_N];

    for (int c = 0; c < cand_count; c++) {
        long long A = candidates[c];
        int filtered_count = 0;

        // 1. Gather all streets completely within the boundaries of [A, A + L]
        for (int i = 0; i < N; i++) {
            if (streets[i].xl >= A && streets[i].xr <= A + L) {
                filtered[filtered_count++] = streets[i];
            }
        }

        if (filtered_count == 0) continue;

        // 2. Sort the valid streets chronologically by their start position
        qsort(filtered, filtered_count, sizeof(Street), compare_streets);

        // 3. Greedily merge intervals to see if we can reach A + L
        long long current_right = A;
        for (int i = 0; i < filtered_count; i++) {
            if (filtered[i].xl > current_right) {
                // Found a missing gap between intervals
                break;
            }
            if (filtered[i].xr > current_right) {
                current_right = filtered[i].xr;
            }
        }

        // Check if the union covers the target interval seamlessly
        if (current_right == A + L) {
            possible = true;
            break;
        }
    }

    if (possible) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}

int main() {
    int T;
    if (scanf("%d", &T) == 1) {
        while (T--) {
            solve_test_case();
        }
    }
    return 0;
}
