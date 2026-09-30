#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node* next;
} Node;
typedef struct Stack {
    Node* head;
} Stack;
void push(Stack* stack, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = stack->head;
    stack->head = new_node;
}
void merge(Stack* stack1, Stack* stack2) {
    if (stack1->head == NULL) {
        stack1->head = stack2->head;
        return;
    }
    if (stack2->head == NULL) {
        return;
    }
    Node* current = stack1->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = stack2->head;
}
void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}
void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    Stack stack1 = {NULL};
    Stack stack2 = {NULL};
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        push(&stack1, val);
    }
    for (int i = 0; i < m; i++) {
        int val;
        scanf("%d", &val);
        push(&stack2, val);
    }
    merge(&stack1, &stack2);
    print_list(stack1.head);
    free_list(stack1.head);
    return 0;
}