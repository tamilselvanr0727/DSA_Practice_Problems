#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 2005

// --- Queue Implementation ---
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

int size(Queue *q) {
    return q->rear - q->front;
}

void enqueue(Queue *q, int x) {
    q->data[q->rear++] = x;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    return q->data[q->front++];
}

int peek(Queue *q) {
    if (isEmpty(q)) return -1;
    return q->data[q->front];
}

// --- Stack implementation using a Single Queue ---
typedef struct {
    Queue q;
} Stack;

void initStack(Stack *s) {
    initQueue(&(s->q));
}

// Push logic matching steps 1, 2, and 3 from the description
void push(Stack *s, int x) {
    // 1) Let size of q be s_size
    int s_size = size(&(s->q));
    
    // 2) Enqueue x to q
    enqueue(&(s->q), x);
    
    // 3) One by one Dequeue s items from queue and enqueue them
    for (int i = 0; i < s_size; i++) {
        int temp = dequeue(&(s->q));
        enqueue(&(s->q), temp);
    }
}

// Pop logic matching step 1 from the description
int pop(Stack *s) {
    // 1) Dequeue an item from q
    return dequeue(&(s->q));
}

int top(Stack *s) {
    return peek(&(s->q));
}

// --- Main Execution Flow ---
int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    Stack s;
    initStack(&s);
    
    // Input format: read and push 'n' element elements
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        push(&s, val);
    }
    
    // Output format: first line indicates top of the element of the stack
    printf("top of element %d\n", top(&s));
    
    // Perform 'm' pop operations
    for (int i = 0; i < m; i++) {
        pop(&s);
    }
    
    // Output format: second line indicates the top of the element after the pop operation
    printf("top of element %d\n", top(&s));
    
    return 0;
}
