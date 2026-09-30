#include <stdio.h>

int min(int a,int b){
    return (a<b)?a:b;
}

int main(){
    int p,q;

    if (scanf("%d %d",&p,&q)==1){
        return 0;
    }

    for (int r=0;r<p;r++){
        for (int c=0;c<q;c++){
            int top=r;
            int left=c;
            int bottom=p-1-r;
            int right=q-1-c;

            int layer=min(min(top,bottom),min(left,right));

            if (layer%2==0){
                putchar('Y');
            }else{
                putchar('0');
            }
        }
        putchar('\n');
    }
    return 0;
}