#include <stdio.h>
#include <stdlib.h>

void solve() {
    int N;
    if (scanf("%d", &N) != 1) return;

    // Dynamically allocate arrays to handle N up to 100,000 without stack overflow
    int *boys_crushes = (int *)malloc((N + 1) * sizeof(int));
    int *girls_crushes = (int *)malloc((N + 1) * sizeof(int));
    
    int *target_boy = (int *)calloc((N + 1), sizeof(int));
    int *target_girl = (int *)calloc((N + 1), sizeof(int));
    
    int *beatings_boy = (int *)calloc((N + 1), sizeof(int));
    int *beatings_girl = (int *)calloc((N + 1), sizeof(int));

    // Input crushes
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &boys_crushes[i]);
    }
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &girls_crushes[i]);
    }

    // Process Boy interactions
    for (int b = 1; b <= N; ++b) {
        int g = boys_crushes[b];
        int target_b = girls_crushes[g];
        if (target_b != b) {
            target_boy[b] = target_b;
            beatings_boy[target_b]++;
        }
    }

    // Process Girl interactions
    for (int g = 1; g <= N; ++g) {
        int b = girls_crushes[g];
        int target_g = boys_crushes[b];
        if (target_g != g) {
            target_girl[g] = target_g;
            beatings_girl[target_g]++;
        }
    }

    // Question 1: Max beatings received by any single student
    int max_beatings = 0;
    for (int i = 1; i <= N; ++i) {
        if (beatings_boy[i] > max_beatings) {
            max_beatings = beatings_boy[i];
        }
        if (beatings_girl[i] > max_beatings) {
            max_beatings = beatings_girl[i];
        }
    }

    // Question 2: Total pairs beating each other (mutual pairs)
    int mutual_pairs = 0;
    for (int b = 1; b <= N; ++b) {
        int tb = target_boy[b];
        // Ensure tb > b to prevent counting the same pair twice
        if (tb > b && target_boy[tb] == b) {
            mutual_pairs++;
        }
    }
    for (int g = 1; g <= N; ++g) {
        int tg = target_girl[g];
        // Ensure tg > g to prevent counting the same pair twice
        if (tg > g && target_girl[tg] == g) {
            mutual_pairs++;
        }
    }

    // Output result for current testcase
    printf("%d %d\n", max_beatings, mutual_pairs);

    // Free dynamically allocated memory
    free(boys_crushes);
    free(girls_crushes);
    free(target_boy);
    free(target_girl);
    free(beatings_boy);
    free(beatings_girl);
}

int main() {
    int T;
    if (scanf("%d", &T) == 1) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
