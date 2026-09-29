#include <stdio.h>
#include <stdlib.h>

// Structure to store element information
typedef struct {
    long long original;
    long long rem;
    long long quot;
} Element;

// Comparator function for qsort
int compareElements(const void* a, const void* b) {
    Element* elemA = (Element*)a;
    Element* elemB = (Element*)b;
    
    // Primary sort: Ascending order of remainders
    if (elemA->rem != elemB->rem) {
        return (elemA->rem < elemB->rem) ? -1 : 1;
    }
    // Secondary sort: Ascending order of quotients
    if (elemA->quot != elemB->quot) {
        return (elemA->quot < elemB->quot) ? -1 : 1;
    }
    return 0;
}

int main() {
    long long M, Q, N;
    
    // Fast I/O for competitive programming
    if (scanf("%lld %lld %lld", &M, &Q, &N) != 3) return 0;
    
    // Dynamically allocate memory for N elements to handle large inputs safely
    Element* arr = (Element*)malloc(N * sizeof(Element));
    if (arr == NULL) return 1;

    for (int i = 0; i < N; ++i) {
        scanf("%lld", &arr[i].original);
        arr[i].rem = arr[i].original % M;
        arr[i].quot = arr[i].original / M;
    }

    // Sort all elements: groups elements with identical remainders together,
    // and sorts their quotients in ascending order within each group.
    qsort(arr, N, sizeof(Element), compareElements);

    long long max_rating = 0;
    int L = 0;

    // Sliding window over the sorted array
    for (int R = 0; R < N; ++R) {
        // If the remainder changes or the value difference exceeds 2 * Q, 
        // shrink the window from the left.
        while (arr[R].rem != arr[L].rem || (arr[R].quot - arr[L].quot) > 2 * Q) {
            L++;
        }
        
        // Calculate current window size
        long long current_window = R - L + 1;
        if (current_window > max_rating) {
            max_rating = current_window;
        }
    }

    printf("%lld\n", max_rating);

    // Free allocated memory
    free(arr);
    return 0;
}
