#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 4000037 // A large prime number to minimize hash collisions

// Node structure for the hash table chaining
typedef struct Node {
    long long value;
    struct Node* next;
} Node;

// Hash function mapping a 64-bit integer to a bucket index
int get_hash(long long val) {
    unsigned long long uval = (unsigned long long)val;
    // Simple mixing strategy to handle negative values properly
    int hash = (int)(uval % HASH_SIZE);
    if (hash < 0) {
        hash += HASH_SIZE;
    }
    return hash;
}

// Inserts a value into the hash table if it doesn't already exist
// Returns 1 if it's a new unique value, 0 otherwise
int insert_unique(Node** hash_table, long long val, long long* total_sum) {
    int index = get_hash(val);
    Node* curr = hash_table[index];
    
    // Check if the value already exists in the chain
    while (curr != NULL) {
        if (curr->value == val) {
            return 0; // Duplicate found
        }
        curr = curr->next;
    }
    
    // Value is unique, create a new node and push it to the front of the chain
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = val;
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
    
    // Add to our running total sum
    *total_sum += val;
    return 1;
}

// Helper macro to find the maximum of two values
long long max_val(long long a, long long b) {
    return (a > b) ? a : b;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long long* a = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; ++i) {
        if (scanf("%lld", &a[i]) != 1) return 0;
    }

    // Allocate and initialize the hash table with NULL pointers
    Node** hash_table = (Node**)calloc(HASH_SIZE, sizeof(Node*));
    long long total_sum = 0;

    // Loop through every possible outer subarray starting index
    for (int i = 0; i < n; ++i) {
        long long ending_here = 0;
        long long max_so_far = a[i];

        // Expand the outer subarray boundary to the right
        for (int j = i; j < n; ++j) {
            if (j == i) {
                ending_here = a[j];
                max_so_far = a[j];
            } else {
                ending_here = max_val(a[j], ending_here + a[j]);
                max_so_far = max_val(max_so_far, ending_here);
            }
            
            // Try inserting the max subarray sum of A[i...j] into our tracker
            insert_unique(hash_table, max_so_far, &total_sum);
        }
    }

    // Output the total sum of unique maximum subarray sums
    printf("%lld\n", total_sum);

    // Free dynamically allocated hash table nodes
    for (int i = 0; i < HASH_SIZE; ++i) {
        Node* curr = hash_table[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    
    // Free arrays
    free(hash_table);
    free(a);

    return 0;
}
