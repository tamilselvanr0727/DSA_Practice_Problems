#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Helper function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to print the linked list in the required format
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("->%d", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Node* head = NULL;
    Node* tail = NULL;

    // Build the linked list from input elements
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        Node* newNode = createNode(val);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    int target;
    scanf("%d", &target);

    // Step 1: Check if the target node exists in the linked list
    Node* current = head;
    bool targetExists = false;
    while (current != NULL) {
        if (current->data == target) {
            targetExists = true;
            break;
        }
        current = current->next;
    }

    // Step 2: Handle the outputs based on whether the target exists
    if (!targetExists) {
        printf("Invalid Node! Linked List:");
        printList(head);
    } else {
        // The new head becomes the target node (implicitly deleting previous nodes)
        Node* newHead = current;
        printf("Linked List:");
        printList(newHead);
    }

    // Free the dynamically allocated memory
    current = head;
    while (current != NULL) {
        Node* nextNode = current->next;
        free(current);
        current = nextNode;
    }

    return 0;
}
