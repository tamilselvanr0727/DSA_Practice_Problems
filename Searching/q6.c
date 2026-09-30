#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort to sort in descending order
int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }
    
    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    
    // Read the array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Step 1: Sort the array in descending order
    qsort(arr, n, sizeof(int), compare_desc);
    
    // Step 2: Find the 3rd unique largest element by skipping duplicates
    int unique_count = 1;
    int third_largest = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[i - 1]) {
            unique_count++;
            if (unique_count == 3) {
                third_largest = arr[i];
                break;
            }
        }
    }
    
    // Print the output strictly matching the expected format
    printf("The third Largest element is %d\n", third_largest);
    
    free(arr);
    return 0;
}
