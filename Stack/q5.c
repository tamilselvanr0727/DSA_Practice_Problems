#include <stdio.h>
#include <string.h>
#define MAX 100
int main(){
    char stack[MAX];
    char exp[MAX];
    int top=-1;
    int i;
    printf("Enter the Expression:");
    scanf("%s",&exp);
    for (i=0;exp[i]!='\0';i++){
        int ch=exp[i];
        if (ch=='(' || exp[i]=='{' || exp[i]=='['){
            stack[top++]=ch;
        }
        else if (ch==')' || ch=='}' || ch==']'){
            if (top==-1){
                printf("Not Balanced!\n");
                return 0;
            }
            char open=stack[top--];
            if ((ch==')' && open=='(') || (ch=='}' && open=='{') || (ch==']' && open=='[')){
                printf("Not Balanced!\n");
                return 0;
            }
        }
    }
    if (top==-1){
        printf("Balanced\n");
    }else{
        printf("Not Balanced\n");
    }
}