#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    // A tree with n nodes has a sequence of length n - 2
    int len = n - 2;
    int *code = (int *)malloc(len * sizeof(int));
    int *degree = (int *)calloc(n + 1, sizeof(int));

    // Initialize all node degrees to 1
    for (int i = 1; i <= n; i++) {
        degree[i] = 1;
    }

    // Read the sequence and increment the degree for each appearance
    for (int i = 0; i < len; i++) {
        scanf("%d", &code[i]);
        degree[code[i]]++;
    }

    // Pointer to find the smallest leaf with O(n) total scanning
    int leaf_ptr = 1;
    while (leaf_ptr <= n && degree[leaf_ptr] != 1) {
        leaf_ptr++;
    }

    int current_leaf = leaf_ptr;

    // Reconstruct the first n - 2 edges
    for (int i = 0; i < len; i++) {
        int neighbor = code[i];
        
        // Print the edge between the leaf and its neighbor
        printf("%d %d\n", current_leaf, neighbor);

        // Remove the leaf from the tree
        degree[current_leaf]--; 
        // Decrement neighbor's degree since it lost a leaf connection
        degree[neighbor]--;

        // If the neighbor becomes a leaf and is smaller than our current pointer,
        // it immediately becomes the next smallest leaf to process.
        if (degree[neighbor] == 1 && neighbor < leaf_ptr) {
            current_leaf = neighbor;
        } else {
            // Otherwise, move the pointer forward to find the next smallest available leaf
            leaf_ptr++;
            while (leaf_ptr <= n && degree[leaf_ptr] != 1) {
                leaf_ptr++;
            }
            current_leaf = leaf_ptr;
        }
    }

    // Connect the final two remaining nodes that have a degree of 1
    int u = 0, v = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            if (u == 0) {
                u = i;
            } else {
                v = i;
                break;
            }
        }
    }
    printf("%d %d\n", u, v);

    // Free allocated memory
    free(code);
    free(degree);

    return 0;
}