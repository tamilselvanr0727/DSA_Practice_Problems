#include <stdio.h>
#include <stdlib.h>

void insertion_sort_with_snapshot(int arr[], int n) {
    int i, key, j;

    // Perform insertion sort
    for (i = 1; i < n; i++) {
        // Print the status of the array at the 3rd iteration
        // (after completing i=1 and i=2, right before i=3 starts)
        if (i == 3) {
            for (int k = 0; k < n; k++) {
                printf("%d%s", arr[k], (k == n - 1) ? "" : " ");
            }
            printf("\n");
        }

        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    // If the array has 3 or fewer elements, the loop never reaches i == 3.
    // In that case, print the array status here before the final print.
    if (n <= 3) {
        for (int k = 0; k < n; k++) {
            printf("%d%s", arr[k], (k == n - 1) ? "" : " ");
        }
        printf("\n");
    }

    // Print the final fully sorted array
    for (int k = 0; k < n; k++) {
        printf("%d%s", arr[k], (k == n - 1) ? "" : " ");
    }
    printf("\n");
}

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    // Allocate memory dynamically to handle larger constraints up to 10^5 safely
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    // Read the array elements
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 0;
        }
    }

    insertion_sort_with_snapshot(arr, n);

    // Free dynamically allocated memory
    free(arr);
    return 0;
}
