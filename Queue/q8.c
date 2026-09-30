#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    
    // Read the number of page references (n) and the cache size (m)
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    
    // Dynamically allocate memory for the input pages sequence
    int *pages = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    // Cache array to keep track of frames, initialized to -1 (empty)
    int *cache = (int *)malloc(m * sizeof(int));
    int current_size = 0;
    for (int i = 0; i < m; i++) {
        cache[i] = -1;
    }
    
    // Process each page reference
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found_index = -1;
        
        // Check if the page is already in the cache (Hit Check)
        for (int j = 0; j < current_size; j++) {
            if (cache[j] == page) {
                found_index = j;
                break;
            }
        }
        
        if (found_index != -1) {
            // PAGE HIT: Shift elements down to bring the hit page to the front
            for (int j = found_index; j > 0; j--) {
                cache[j] = cache[j - 1];
            }
            cache[0] = page;
        } else {
            // PAGE MISS
            if (current_size < m) {
                // Cache is not full: shift everything right and insert at front
                for (int j = current_size; j > 0; j--) {
                    cache[j] = cache[j - 1];
                }
                cache[0] = page;
                current_size++;
            } else {
                // Cache is full: evict rear element (cache[m-1]) by shifting right
                for (int j = m - 1; j > 0; j--) {
                    cache[j] = cache[j - 1];
                }
                cache[0] = page;
            }
        }
    }
    
    // Print the final cache state separated by spaces
    for (int i = 0; i < current_size; i++) {
        printf("%d", cache[i]);
        if (i < current_size - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    // Clean up allocated memory
    free(pages);
    free(cache);
    
    return 0;
}
