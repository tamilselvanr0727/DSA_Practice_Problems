#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// Structure to implement the stack of strings
struct Stack {
    int top;
    char data[MAX][MAX];
};

// Function to push a string onto the stack
void push(struct Stack* s, char* str) {
    if (s->top >= MAX - 1) {
        return;
    }
    s->top++;
    strcpy(s->data[s->top], str);
}

// Function to pop a string from the stack
void pop(struct Stack* s, char* target) {
    if (s->top < 0) {
        return;
    }
    strcpy(target, s->data[s->top]);
    s->top--;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int main() {
    char postfix[MAX];
    struct Stack s;
    s.top = -1;

    // Read the postfix expression from standard input
    if (scanf("%s", postfix) != 1) {
        return 0;
    }

    int length = strlen(postfix);

    // Process the postfix expression from left to right
    for (int i = 0; i < length; i++) {
        char c = postfix[i];

        if (isOperator(c)) {
            char op1[MAX], op2[MAX], temp[MAX];

            // Pop two operands from the stack
            pop(&s, op2);
            pop(&s, op1);

            // Concatenate: operator + operand1 + operand2
            sprintf(temp, "%c%s%s", c, op1, op2);

            // Push the resultant string back to the stack
            push(&s, temp);
        } else {
            // If the symbol is an operand, push it onto the stack as a string
            char str[2] = {c, '\0'};
            push(&s, str);
        }
    }

    // The final prefix expression remains at the top of the stack
    char result[MAX];
    pop(&s, result);

    printf("%s\n", result);

    return 0;
}
