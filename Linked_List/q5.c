#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to delete alternate nodes starting from the second node
void deleteAlternateNodes(struct Node* head) {
    if (head == NULL) return;

    // Follow the function description step-by-step:
    // 1. Take two pointers a and b.
    // 2. Let initially a points to head and b points to pointer of a, that is second node.
    struct Node* a = head;
    struct Node* b = head->next;

    // 5. Continue loop until a and b becomes NULL
    while (a != NULL && b != NULL) {
        // 3. Then make the link of a to point to pointer of b
        a->next = b->next;

        // Free b (delete the alternate node from memory)
        free(b);

        // 4. Next is move a to its pointer that is next node
        a = a->next;

        // 4. Next is move b to next node of a
        if (a != NULL) {
            b = a->next;
        } else {
            b = NULL;
        }
    }
}

// Helper function to print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    // Create the sequential linked list from 1 to n based on the test cases
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    head->data = 1;
    head->next = NULL;
    
    struct Node* tail = head;
    for (int i = 2; i <= n; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = i;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }

    // Delete alternate nodes
    deleteAlternateNodes(head);

    // Print the modified list elements
    printList(head);

    // Free the remaining memory to prevent memory leaks
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
