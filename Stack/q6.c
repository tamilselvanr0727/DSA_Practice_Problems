#include <stdio.h>
#include <stdlib.h>
void calculateStockSpan(int n, int *prices) {
    int *span = (int *)malloc(n * sizeof(int));
    int *stack = (int *)malloc(n * sizeof(int));
    int top = -1; 
    for (int i = 0; i < n; i++) {
        while (top >= 0 && prices[stack[top]] <= prices[i]) {
            top--;
        }
        if (top == -1) {
            span[i] = i + 1;
        } else {
            span[i] = i - stack[top];
        }
        top++;
        stack[top] = i;
    }
    for (int i = 0; i < n; i++) {
        printf("%d", span[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
    free(span);
    free(stack);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int *prices = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &prices[i]) != 1) break;
    }
    calculateStockSpan(n, prices);
    free(prices);
    return 0;
}