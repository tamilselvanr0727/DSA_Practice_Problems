#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, D;

    // Read the total number of elements
    if (scanf("%d", &N) != 1) {
        return 0;
    }

    // Allocate memory to store the list elements
    int *arr = (int *)malloc(N * sizeof(int));
    if (arr == NULL) {
        return 1; // Memory allocation failed
    }

    // Read the N elements of the linked list
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 0;
        }
    }

    // Read the number of nodes to delete
    if (scanf("%d", &D) != 1) {
        free(arr);
        return 0;
    }

    // Print the output header
    printf("Linked List:->");

    // Print the remaining elements starting from index D up to N-1
    for (int i = D; i < N; i++) {
        printf("%d", arr[i]);
        
        // Print the arrow connector only if it's not the last element
        if (i < N - 1) {
            printf("->");
        }
    }
    printf("\n");

    // Clean up allocated memory
    free(arr);

    return 0;
}
