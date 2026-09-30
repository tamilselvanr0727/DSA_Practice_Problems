#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the linked list queue
struct Node {
    int data;
    struct Node* next;
};

// Global pointers for front and rear of the queue
struct Node* front = NULL;
struct Node* rear = NULL;

// Function to insert an element into the queue (at the rear)
void enqueue(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return; // Memory allocation failed
    }
    newNode->data = value;
    newNode->next = NULL;
    
    if (front == NULL && rear == NULL) {
        // Queue is empty
        front = rear = newNode;
    } else {
        // Link the old rear to the new node, then update rear
        rear->next = newNode;
        rear = newNode;
    }
}

// Function to remove an element from the queue (from the front)
void dequeue() {
    if (front == NULL) {
        return; // Queue is underflow/empty
    }
    
    struct Node* temp = front;
    front = front->next;
    
    // If queue becomes empty, set rear to NULL as well
    if (front == NULL) {
        rear = NULL;
    }
    
    free(temp);
}

// Function to print the entire queue from front to rear
void displayQueue() {
    if (front == NULL) {
        printf("\n");
        return;
    }
    
    struct Node* temp = front;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" ");
        }
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n, value;
    
    // Read the total number of elements to insert
    if (scanf("%d", &n) != 1) return 0;
    
    // Insert all elements into the queue
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &value) == 1) {
            enqueue(value);
        }
    }
    
    // Line 1: Print queue after all insertions
    displayQueue();
    
    // Line 2: Print queue after the 1st dequeue operation
    dequeue();
    displayQueue();
    
    // Line 3: Print queue after the 2nd dequeue operation
    dequeue();
    displayQueue();
    
    return 0;
}
