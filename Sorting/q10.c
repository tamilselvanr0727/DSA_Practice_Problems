#include <stdio.h>
#include <stdlib.h>

// Structure to store each flat's diagonal projection and its population
typedef struct {
    long long d; // y - x
    long long h; // population
} Flat;

// Comparator function to sort flats by their 'd' value in ascending order
int compareFlats(const void *a, const void *b) {
    long long diff = ((Flat *)a)->d - ((Flat *)b)->d;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

void solve() {
    int n;
    if (scanf("%d", &n) != 1) return;

    Flat *flats = (Flat *)malloc(n * sizeof(Flat));
    long long total_people = 0;

    for (int i = 0; i < n; i++) {
        long long x, y, h;
        scanf("%lld %lld %lld", &x, &y, &h);
        flats[i].d = y - x;
        flats[i].h = h;
        total_people += h;
    }

    // Sort all entries by their y - x diagonal value
    qsort(flats, n, sizeof(Flat), compareFlats);

    int possible = 0;
    long long running_prefix = 0;
    
    int i = 0;
    while (i < n) {
        int j = i;
        long long current_group_weight = 0;

        // Group together all flats that lie exactly on the same diagonal line
        while (j < n && flats[j].d == flats[i].d) {
            current_group_weight += flats[j].h;
            j++;
        }

        running_prefix += current_group_weight;
        long long left_side_inclusive = running_prefix;
        long long right_side_exclusive = total_people - running_prefix;

        // Condition 1: The divider line is placed strictly between this diagonal and the next
        if (left_side_inclusive == right_side_exclusive) {
            possible = 1;
            break;
        }

        // Condition 2: The divider line passes directly through this diagonal group (excluding its weight)
        if ((left_side_inclusive - current_group_weight) == right_side_exclusive) {
            possible = 1;
            break;
        }

        i = j; // Move to the next distinct diagonal
    }

    if (possible) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    free(flats);
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
