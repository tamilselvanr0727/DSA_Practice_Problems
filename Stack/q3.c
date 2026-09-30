#include <stdio.h>
#include <stdlib.h>
#define MAX_DIGIT_SUM 82
typedef struct {
    int index;
    int value;
} StackElement;
int get_digit_sum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
int main() {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;
    int *A = (int *)malloc((N + 1) * sizeof(int));
    int *digit_sums = (int *)malloc((N + 1) * sizeof(int));
    int *ans = (int *)malloc((N + 1) * sizeof(int));
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        digit_sums[i] = get_digit_sum(A[i]);
        ans[i] = -1; 
    }
    StackElement *stacks[MAX_DIGIT_SUM];
    int stack_sizes[MAX_DIGIT_SUM] = {0};
    int stack_capacities[MAX_DIGIT_SUM] = {0};
    for (int s = 1; s < MAX_DIGIT_SUM; s++) {
        stack_capacities[s] = 4; 
        stacks[s] = (StackElement *)malloc(stack_capacities[s] * sizeof(StackElement));
    }
    for (int i = N; i >= 1; i--) {
        int curr_val = A[i];
        int curr_sum = digit_sums[i];
        int min_idx = N + 1; 
        for (int s = 1; s < curr_sum; s++) {
            if (stack_sizes[s] > 0) {
                StackElement top = stacks[s][stack_sizes[s] - 1];
                if (top.value > curr_val) {
                    if (top.index < min_idx) {
                        min_idx = top.index;
                    }
                }
            }
        }
        if (min_idx != N + 1) {
            ans[i] = min_idx;
        }
        while (stack_sizes[curr_sum] > 0 && stacks[curr_sum][stack_sizes[curr_sum] - 1].value <= curr_val) {
            stack_sizes[curr_sum]--;
        }
        if (stack_sizes[curr_sum] >= stack_capacities[curr_sum]) {
            stack_capacities[curr_sum] *= 2;
            stacks[curr_sum] = (StackElement *)realloc(stacks[curr_sum], stack_capacities[curr_sum] * sizeof(StackElement));
        }
        stacks[curr_sum][stack_sizes[curr_sum]].index = i;
        stacks[curr_sum][stack_sizes[curr_sum]].value = curr_val;
        stack_sizes[curr_sum]++;
    }
    for (int q = 0; q < Q; q++) {
        int query_idx;
        scanf("%d", &query_idx);
        printf("%d%c", ans[query_idx], (q == Q - 1) ? '\n' : ' ');
    }
    for (int s = 1; s < MAX_DIGIT_SUM; s++) {
        free(stacks[s]);
    }
    free(A);
    free(digit_sums);
    free(ans);
    return 0;
}