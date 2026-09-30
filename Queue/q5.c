#include <stdio.h>
#define SIZE 100

int queue[SIZE];
int front=-1;
int rear=-1;

void enqueue(int data){
    if (rear==SIZE-1){
        printf("queue overflow\n");
        return;
    }

    if (front==-1){
        front=0;
    }
    rear++;
    queue[rear]=data;
}

void disp(){
    if (front==-1){
        return;
    }
    for (int i=front;i<=rear;i++){
        printf("%d ",queue[i]);
    }
}

int main(){
    int n,data;

    printf("Enter how many elements?");
    scanf("%d",&n);

    for (int i = 0; i < SIZE; i++) {
        if (scanf("%d", &data) == 1) {
            disp();
            printf("Enqueuing %d\n", data);
            enqueue(data);
        }
    }

    disp();
    printf("\n");
    return 0;
}