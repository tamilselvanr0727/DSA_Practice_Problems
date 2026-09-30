#include <stdio.h>

#define MAX_SIZE 100

// Global queue and its boundaries as specified by the function description
int queue[MAX_SIZE];
int front = -1;
int rear = -1;

// Function to add elements to the queue
void enqueue(int data) {
    if (rear == MAX_SIZE - 1) {
        return; // Queue overflow
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    queue[rear] = data;
}

// Function to reverse the queue elements using the loop logic from the description
void reverseQueue() {
    // Implementing: MAKE A FOR LOOP (I=FRONT, J=REAR; I<J; I++, J--)
    // Note: The image says J++, but standard reversal logic requires J-- to move towards the center.
    for (int i = front, j = rear; i < j; i++, j--) {
        // SWAP(FRONT, REAR) values at index i and j
        int temp = queue[i];
        queue[i] = queue[j];
        queue[j] = temp;
    }
}

int main() {
    int size;
    
    // Read the size of the queue
    if (scanf("%d", &size) != 1) return 0;
    
    // Call enqueue function while (i < given size of queue)
    printf("Queue:");
    for (int i = 0; i < size; i++) {
        int element;
        scanf("%d", &element);
        enqueue(element);
        printf("%d ", element);
    }
    printf("\n");
    
    // Call reverse function
    reverseQueue();
    
    // Print the reversed elements
    printf("Reversed Queue:");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
    
    return 0;
}
