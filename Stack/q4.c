#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
struct TwoStacks {
    int arr[MAX_SIZE];
    int top1;
    int top2;
};
void init(struct TwoStacks *ts) {
    ts->top1 = -1;
    ts->top2 = MAX_SIZE;
}
void push1(struct TwoStacks *ts, int x) {
    if (ts->top1 < ts->top2 - 1) {
        ts->top1++;
        ts->arr[ts->top1] = x;
    }
}
void push2(struct TwoStacks *ts, int x) {
    if (ts->top1 < ts->top2 - 1) {
        ts->top2--;
        ts->arr[ts->top2] = x;
    }
}
int pop1(struct TwoStacks *ts) {
    if (ts->top1 >= 0) {
        int x = ts->arr[ts->top1];
        ts->top1--;
        return x;
    }
    return -1;
}
int pop2(struct TwoStacks *ts) {
    if (ts->top2 < MAX_SIZE) {
        int x = ts->arr[ts->top2];
        ts->top2++;
        return x;
    }
    return -1;
}

int main() {
    struct TwoStacks ts;
    init(&ts);
    int val;
    for (int i = 0; i < 5; i++) {
        if (scanf("%d", &val) != 1) {
            break;
        }
        if (i % 2 == 0) {
            push1(&ts, val);
        } else {
            push2(&ts, val);
        }
    }
    printf("Popped element from stack1 is:%d\n", pop1(&ts));
    printf("Popped element from stack2 is:%d\n", pop2(&ts));
    return 0;
}