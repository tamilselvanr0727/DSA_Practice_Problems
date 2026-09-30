#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the circular linked list
struct Node {
    int data;
    struct Node* next;
};

// Structure for the Circular Queue
struct CircularQueue {
    struct Node* front;
    struct Node* rear;
};

// Function to initialize the queue
void initQueue(struct CircularQueue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Function to insert an element into the circular queue
void enqueue(struct CircularQueue* q, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    // If the queue is empty
    if (q->front == NULL) {
        q->front = newNode;
        q->rear = newNode;
        newNode->next = q->front; // Circular link to itself
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
        q->rear->next = q->front; // Maintain circular link to front
    }

    // Print the inserted element as required by the first output line
    printf("%d\n", value);
}

// Function to remove an element from the circular queue
int dequeue(struct CircularQueue* q) {
    if (q->front == NULL) {
        return -1; // Queue is empty
    }

    int dequeuedValue = q->front->data;
    struct Node* temp = q->front;

    // If there is only one element in the queue
    if (q->front == q->rear) {
        q->front = NULL;
        q->rear = NULL;
        free(temp);
    } else {
        q->front = q->front->next;
        q->rear->next = q->front; // Update the circular link
        free(temp);
    }

    return dequeuedValue;
}

int main() {
    int n, value;
    struct CircularQueue q;
    initQueue(&q);

    // Read the size of the queue
    if (scanf("%d", &n) != 1) return 0;

    // Read and enqueue all elements
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &value) == 1) {
            enqueue(&q, value);
        }
    }

    // Dequeue one element and print it as required by the second output line
    int removedElement = dequeue(&q);
    if (removedElement != -1) {
        printf("%d\n", removedElement);
    }

    return 0;
}
