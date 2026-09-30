#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 100003  // A prime number for better hash distribution

// Structure for Hash Table Nodes
typedef struct Node {
    int age;
    int count;
    struct Node* next;
} Node;

// Hash Table structure
Node* hashTable[HASH_SIZE];

// Hash function
int getHash(int age) {
    return age % HASH_SIZE;
}

// Function to update the title count of a ghost and return the new count
int updateAndGetCount(int age) {
    int index = getHash(age);
    Node* current = hashTable[index];
    
    // Search if the ghost is already in the hash table
    while (current != NULL) {
        if (current->age == age) {
            current->count++;
            return current->count;
        }
        current = current->next;
    }
    
    // If not found, insert a new node at the beginning of the chain
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->age = age;
    newNode->count = 1;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    
    return 1;
}

// Helper function to free the dynamically allocated memory
void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    int N, M;
    // Fast I/O configuration
    if (scanf("%d %d", &N, &M) != 2) return 0;
    
    int current_leader = -1;
    int max_titles = -1;
    
    // Initialize Hash Table to NULL
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
    
    // Process each day's winner
    for (int i = 0; i < N; i++) {
        int ghost_winner;
        if (scanf("%d", &ghost_winner) != 1) break;
        
        // Update counts and fetch the updated title total
        int current_count = updateAndGetCount(ghost_winner);
        
        // Leader update evaluation logic
        if (current_count > max_titles) {
            max_titles = current_count;
            current_leader = ghost_winner;
        } 
        else if (current_count == max_titles) {
            // Tie-breaker rule: Eldest ghost wins
            if (ghost_winner > current_leader) {
                current_leader = ghost_winner;
            }
        }
        
        // Print the result for the current day
        printf("%d %d\n", current_leader, max_titles);
    }
    
    // Cleanup allocated memory
    freeHashTable();
    
    return 0;
}
