#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to push a node to the front of the linked list
void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Function to print the linked list in the required format
void printList(struct Node* node) {
    printf("Linked list:--- >");
    while (node != NULL) {
        printf("%d", node->data);
        if (node->next != NULL) {
            printf("--->");
        }
        node = node->next;
    }
    printf("\n");
}

// Function to get the data value at the given index (0-based)
int GetNth(struct Node* head, int index) {
    struct Node* current = head;
    int count = 0;
    while (current != NULL) {
        if (count == index) {
            return current->data;
        }
        count++;
        current = current->next;
    }
    // Return -1 if index is out of bounds
    return -1;
}

// Driver program to test above functions
int main() {
    int n, value, index;
    struct Node* head = NULL;

    // Read the number of elements
    if (scanf("%d", &n) != 1) return 0;

    // Read the list elements and push them onto the stack-based linked list
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &value) == 1) {
            push(&head, value);
        }
    }

    // Read the required index
    if (scanf("%d", &index) != 1) return 0;

    // Print results matching the test case expectations exactly
    printList(head);
    int result = GetNth(head, index);
    printf("Node at index=%d:%d\n", index, result);

    // Free allocated memory
    struct Node* current = head;
    struct Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    return 0;
}
