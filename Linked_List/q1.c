#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

int main(){
    int n;
    if (scanf("%d",&n)!=1) return 0;

    Node *head=NULL;
    Node *tail=NULL;

    for (int i=0;i<n;i++){
        int val;
        scanf("%d",&val);

        Node *newNode;
        newNode=(Node *)malloc(sizeof(Node));
        newNode->data=val;
        newNode->next=NULL;

        if (head==NULL){
            head=newNode;
            tail=newNode;
        }else{
            tail->next=newNode;
            tail=newNode;
        }
    }

    int target;
    scanf("%d",&target);

    Node *current=head;
    Node *previous=NULL;

    while (current!=NULL){
        if (current->data==target){
            if (current==head){
                head=current->next;
                free(current);
                current=head;
            }else{
                previous->next=current->next;
                free(current);
                current=previous->next;
            }
        }else{
            previous=current;
            current=current->next;
        }
    }

    printf("Linked List:");
    Node *temp=head;
    while (temp!=NULL){
        printf("%d",temp->data);
        if (temp->next!=NULL){
            printf("->");
        }
        temp=temp->next;
    }
    printf("\n");
    return 0;
}