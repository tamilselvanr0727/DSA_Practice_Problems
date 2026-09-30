#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

Node* createNode(int value){
    Node *newNode;
    newNode=(Node *)malloc(sizeof(Node));
    newNode->data=value;
    newNode->next=NULL;
    return newNode;
}

void sortedInsert(Node** head,int value){
    Node* newNode=createNode(value);
    Node* present=*head;

    if (present==NULL){
        newNode->next=newNode;
        *head=newNode;
        return;
    }

    if (value<present->data){
        while (present->next!=*head){
            present=present->next;
        }
        present->next=newNode;
        newNode->next=*head;
        *head=newNode;
    }else{
        while(present->next!=*head && present->next->data<value){
            present=present->next;
        }
        newNode->next=present->next;
        present->next=newNode;
    }
}

void print(Node *head){
    if (head==NULL) return;

    Node *temp=head;
    do{
        printf("%d ",temp->data);
    }while(temp!=head);
    printf("\n");
}

int main(){
    int n,value;

    if (scanf("%d",&n)!=1) return 0;
    Node *head=NULL;

    for (int i=0;i<n;i++){
        scanf("%d",&value);
        sortedInsert(&head,value);
    }

    print(head);
    return 0;
}
