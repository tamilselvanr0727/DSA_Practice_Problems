#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

Node *front=NULL;
Node *rear=NULL;

void enqueue(int value){
    Node* newNode=(Node *)malloc(sizeof(Node));
    newNode->data=value;
    newNode->next=NULL;
    if (front==NULL && rear==NULL){
        front=newNode;
        rear=newNode;
    }else{
        rear->next=newNode;
        rear=newNode;
    }
}

void dequeue(){
    if (front==NULL){
        return;
    }

    Node *temp=front;
    front=front->next;

    if (front==NULL){
        rear==NULL;
    }
    free(temp);
}

void print(){
    if (front==NULL){
        printf("No data\n");
        return;
    }

    Node *temp=front;
    while (temp!=NULL){
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter How many Elements?");
    scanf("%d",&n);

    for (int i=0;i<n;i++){
        int data;
        scanf("%d",&data);
        enqueue(data);
    }

    print();
    dequeue();
    print();

    return 0;
}