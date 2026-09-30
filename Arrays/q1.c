#include <stdio.h>
#include <stdlib.h>

typedef struct mappings{
    int value;
    const char *symbol;
}mappings;

int Martian(int num){
    mappings map[]={
        {1000,"R"},{900,"BR"},{500,"G"},{400,"BG"},
        {100,"B"},{90,"ZB"},{50,"P"},{40,"ZP"},
        {10, "Z"},   {9, "BZ"},   {5, "W"},   {4, "BW"},
        {1, "B"}
    };

    int num_ele=sizeof(map)/sizeof(map[0]);
    for (int i=0;i<num_ele;i++){
        if (num>=map[i].value){
            printf("%s",map[i].symbol);
            num-=map[i].value;
        }
    }
    printf("\n");
}

int main(){
    int num;

    while (scanf("%d",&num)==1){
        Martian(num);
    }
    return 0;
}