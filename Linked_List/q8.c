#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition for singly-linked list node.
struct ListNode {
    int val;
    struct ListNode* next;
};

// Function to create a new node
struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// Function to print the linked list in the required format
void printList(struct ListNode* head) {
    struct ListNode* curr = head;
    while (curr != NULL) {
        printf("%d", curr->val);
        if (curr->next != NULL) {
            printf(" ");
        }
        curr = curr->next;
    }
    printf("\n");
}

// Function to reverse a linked list
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    struct ListNode* nextNode = NULL;
    while (curr != NULL) {
        nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}

// Function to fold the linked list according to the rules
struct ListNode* foldList(struct ListNode* head) {
    if (!head || !head->next) return head;

    // Step 2 & 3: Find middle using slow and fast pointers
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    struct ListNode* prevSlow = NULL;

    while (fast != NULL && fast->next != NULL) {
        prevSlow = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    struct ListNode* secondHalfHead = NULL;
    
    if (fast == NULL) {
        // Even number of nodes: split exactly before the slow pointer
        prevSlow->next = NULL;
        secondHalfHead = slow;
    } else {
        // Odd number of nodes: the exact middle node stays with the first half
        secondHalfHead = slow->next;
        slow->next = NULL;
    }

    // Step 4: Reverse the second half
    secondHalfHead = reverseList(secondHalfHead);

    // Step 5: Alternate merge the first half and the reversed second half
    struct ListNode* first = head;
    struct ListNode* second = secondHalfHead;
    
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    bool toggle = true;

    while (first != NULL && second != NULL) {
        if (toggle) {
            tail->next = first;
            first = first->next;
        } else {
            tail->next = second;
            second = second->next;
        }
        tail = tail->next;
        toggle = !toggle;
    }

    // Append any remaining items
    if (first != NULL) tail->next = first;
    if (second != NULL) tail->next = second;

    return dummy.next;
}

// Function to safely free linked list memory
void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    if (n <= 0) {
        printf("Link list data:\n");
        printf("Link list data after fold:\n");
        return 0;
    }

    struct ListNode* head = NULL;
    struct ListNode* tail = NULL;
    
    struct ListNode* origHead = NULL;
    struct ListNode* origTail = NULL;

    for (int i = 0; i < n; ++i) {
        int val;
        if (scanf("%d", &val) != 1) break;
        
        // Build tracking list for manipulation
        struct ListNode* newNode = createNode(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        // Build a backup list to display the original formatting safely
        struct ListNode* origNode = createNode(val);
        if (!origHead) {
            origHead = origNode;
            origTail = origNode;
        } else {
            origTail->next = origNode;
            origTail = origNode;
        }
    }

    // Output original linked list state
    printf("Link list data:");
    printList(origHead);

    // Execute list fold logic
    struct ListNode* foldedHead = foldList(head);

    // Output final folded state
    printf("Link list data after fold:");
    printList(foldedHead);

    // Clean up heap allocated memory pointers
    freeList(origHead);
    freeList(foldedHead);

    return 0;
}
