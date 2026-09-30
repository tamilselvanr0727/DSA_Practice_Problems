#include <stdio.h>
#include <stdlib.h>

// Define the structure for a circular linked list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Helper function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to print a circular linked list matching the required format
void printCircularList(Node* head) {
    printf("[h]");
    if (head != NULL) {
        Node* temp = head;
        do {
            printf("=>%d", temp->data);
            temp = temp->next;
        } while (temp != head);
    }
    printf("=>[h]\n");
}

// Function to free the memory of a circular linked list
void freeCircularList(Node* head) {
    if (head == NULL) return;
    Node* current = head;
    Node* nextNode;
    do {
        nextNode = current->next;
        free(current);
        current = nextNode;
    } while (current != head);
}

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    // 1. Create the Complete Circular Linked List (1 to n)
    Node* completeHead = createNode(1);
    Node* current = completeHead;
    for (int i = 2; i <= n; i++) {
        current->next = createNode(i);
        current = current->next;
    }
    current->next = completeHead; // Link back to head to make it circular

    // 2. Create the Odd Circular Linked List
    Node* oddHead = createNode(1);
    current = oddHead;
    for (int i = 3; i <= n; i += 2) {
        current->next = createNode(i);
        current = current->next;
    }
    current->next = oddHead;

    // 3. Create the Even Circular Linked List
    Node* evenHead = NULL;
    if (n >= 2) {
        evenHead = createNode(2);
        current = evenHead;
        for (int i = 4; i <= n; i += 2) {
            current->next = createNode(i);
            current = current->next;
        }
        current->next = evenHead;
    }

    // --- Print Outputs ---
    printf("Complete linked_list:\n");
    printCircularList(completeHead);

    printf("Odd:\n");
    printCircularList(oddHead);

    printf("Even:\n");
    printCircularList(evenHead);

    // --- Free Memory ---
    freeCircularList(completeHead);
    freeCircularList(oddHead);
    if (evenHead != NULL) {
        freeCircularList(evenHead);
    }

    return 0;
}
