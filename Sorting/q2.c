#include <stdio.h>
#include <stdlib.h>

// Function to perform Selection Sort
void selectionSort(long long arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element of unsorted part
        long long temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    
    // Dynamically allocate memory for the array
    // Using long long because the constraints mention elements up to 10^9
    long long *arr = (long long *)malloc(n * sizeof(long long));
    if (arr == NULL) {
        return 1; // Memory allocation failed
    }
    
    // Read the array elements
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }
    
    // Execute the sorting algorithm
    selectionSort(arr, n);
    
    // Print the sorted elements separated by space
    for (int i = 0; i < n; i++) {
        printf("%lld", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    // Free the allocated memory
    free(arr);
    
    return 0;
}
