#include <stdio.h>
#define SIZE 100

int queue[SIZE];
int front=-1;
int rear=-1;

void enqueue(int ele){
    if (rear==SIZE-1){
        printf("Queue Overflow\n");
    }
    if (front==-1){
        front=0;
    }
    rear++;
    queue[rear]=ele;

}

void dequeue(){
    if (front==-1 || front>rear){
        printf("Queue is Empty\n");
    }else{
        front++;
        if (front<=rear){
            for (int i=front;i<=rear;i++){
                printf("%d ",queue[i]);
            }
            printf("\n");
        }
        
    }
}

int main(){
    int n,data;
    printf("Enter how many Elements?");
    scanf("%d",&n);

    for (int i=0;i<n;i++){
        scanf("%d",&data);
        enqueue(data);
    }

    printf("\n");
    for (int i=0;i<n-1;i++){
        dequeue();
    }
    return 0;
}