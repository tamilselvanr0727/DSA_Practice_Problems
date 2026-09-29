#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_SIZE 200003 // A prime number close to max N for efficient hashing

// Structure for hash map / hash set nodes
typedef struct Node {
    int key;
    int value; // Used to store the first occurrence index
    struct Node* next;
} Node;

// Hash table array
Node* hash_table[HASH_SIZE];

// Simple hash function for integers
int get_hash(int key) {
    int hash = key % HASH_SIZE;
    if (hash < 0) hash += HASH_SIZE;
    return hash;
}

// Insert element into the hash table if it doesn't exist
// Returns true if inserted (unique), false if it already existed
bool insert_set(int key) {
    int index = get_hash(key);
    Node* curr = hash_table[index];
    while (curr != NULL) {
        if (curr->key == key) {
            return false; // Already exists
        }
        curr = curr->next;
    }
    // Create new node
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
    return true;
}

// Find an element's value (index) in the map
// Returns the index if found, or -1 if not found
int find_map(int key) {
    int index = get_hash(key);
    Node* curr = hash_table[index];
    while (curr != NULL) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }
    return -1;
}

// Insert a key-value pair into the map if the key is missing
void insert_map(int key, int value) {
    if (find_map(key) != -1) return; // Already present
    
    int index = get_hash(key);
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}

// Helper function to free allocated memory
void clear_hash_table() {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = hash_table[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        hash_table[i] = NULL;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Step 1: Calculate distinct elements strictly to the right of each index
    int* suffix_distinct = (int*)calloc(n, sizeof(int));
    int distinct_count_right = 0;

    // Reset hash table to use it as a 'set'
    for (int i = 0; i < HASH_SIZE; i++) hash_table[i] = NULL;

    for (int i = n - 1; i >= 0; i--) {
        suffix_distinct[i] = distinct_count_right;
        if (insert_set(a[i])) {
            distinct_count_right++;
        }
    }

    // Step 2: Track the first occurrence index of each unique element
    clear_hash_table(); // Free previous set memory

    for (int i = 0; i < n; i++) {
        insert_map(a[i], i);
    }

    // Step 3: Compute total unique pairs by checking all unique values
    long long total_special_pikachus = 0;
    
    // Iterate through the hash table map to aggregate counts
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = hash_table[i];
        while (curr != NULL) {
            int first_idx = curr->value;
            total_special_pikachus += suffix_distinct[first_idx];
            curr = curr->next;
        }
    }

    printf("%lld\n", total_special_pikachus);

    // Cleanup
    clear_hash_table();
    free(a);
    free(suffix_distinct);

    return 0;
}
