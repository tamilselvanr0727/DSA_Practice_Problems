#include <stdio.h>
#include <stdlib.h>
int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    long long *A = (long long *)malloc(N * sizeof(long long));
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }
    int *F = (int *)malloc(N * sizeof(int));
    int *G = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        F[i] = -1;
        G[i] = -1;
    }
    int *stack = (int *)malloc(N * sizeof(int));
    int top = -1;
    for (int i = 0; i < N; i++) {
        while (top >= 0 && A[stack[top]] < A[i]) {
            F[stack[top]] = i;
            top--;
        }
        stack[++top] = i;
    }
    top = -1;
    for (int i = 0; i < N; i++) {
        while (top >= 0 && A[stack[top]] > A[i]) {
            G[stack[top]] = i;
            top--;
        }
        stack[++top] = i;
    }
    for (int i = 0; i < N; i++) {
        int next_greater_idx = F[i];
        
        if (next_greater_idx == -1) {
            printf("-1");
        } else {
            int next_smaller_idx = G[next_greater_idx];
            if (next_smaller_idx == -1) {
                printf("-1");
            } else {
                printf("%lld", A[next_smaller_idx]);
            }
        }
        if (i < N - 1) {
            printf(" ");
        }
    }
    printf("\n");
    free(A);
    free(F);
    free(G);
    free(stack);
    return 0;
}