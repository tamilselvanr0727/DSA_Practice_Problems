#include <stdio.h>
#include <stdlib.h>

// Node structure for Circular Linked List
struct Node {
    int data;
    struct Node* next;
};

struct Node* rear = NULL;

// Function to insert an element into the circular queue
void enqueue(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    if (rear == NULL) {
        rear = newNode;
        rear->next = rear;
    } else {
        newNode->next = rear->next;
        rear->next = newNode;
        rear = newNode;
    }
}

// Function to delete an element from the circular queue
int dequeue() {
    if (rear == NULL) {
        return -1;
    }
    struct Node* front = rear->next;
    int val = front->data;
    if (front == rear) {
        free(front);
        rear = NULL;
    } else {
        rear->next = front->next;
        free(front);
    }
    return val;
}

// Function to display the elements in the circular queue
void display() {
    if (rear == NULL) return;
    struct Node* temp = rear->next;
    printf("Elements in Circular Queue are:");
    do {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp != rear->next) {
            printf(" ");
        }
    } while (temp != rear->next);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        enqueue(val);
    }
    
    // Display initial queue
    display();
    printf("\n");
    
    // First Dequeue
    int val1 = dequeue();
    printf("Deleted value = %d\n", val1);
    
    // Second Dequeue (Notice: No newline at the end of this print statement 
    // to match the exact concatenated test case output format)
    int val2 = dequeue();
    printf("Deleted value = %d", val2);
    
    // Display remaining queue
    display();
    printf("\n");
    
    return 0;
}
