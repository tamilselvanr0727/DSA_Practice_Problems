#include <stdio.h>
#include <stdlib.h>

struct Item{
    char name[50];
    int price;
};

int main(){
    int budget;
    int no_items;

    if (scanf("%d %d",&budget,&no_items)!=2){
        return 0;
    }

    struct Item items[10];
    for (int i=0;i<no_items;i++){
        scanf("%s %d",&items[i].name,&items[i].price);
    }

    for (int i=0;i<no_items;i++){
        for (int j=0;j<no_items-i-1;j++){
            if (items[j].price>items[j+1].price){
                struct Item temp=items[j];
                items[j]=items[j+1];
                items[j+1]=temp;
            }
        }
    }

    int count=0;
    for (int i=0;i<no_items;i++){
        if (budget>=items[i].price){
            printf("I can afford %s\n",items[i].name);
            budget=budget-items[i].price;
            count++;
        }else{
            printf("I can't afford %s\n",items[i].name);
        }
    }

    if (count==0){
        printf("I need more money\n");
    }
    printf("%d\n",count);
    return 0;
}