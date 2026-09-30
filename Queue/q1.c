#include <stdio.h>

int main(){
    int n;
    if (scanf("%d",&n)!=1) return 0;

    long long max1=-1;
    long long max2=-1;
    long long max3=-1;

    for (int i=0;i<n;i++){
        long long num;
        scanf("%lld",&num);
        if (num>max1){
            max3=max2;
            max2=max1;
            max1=num;
        }else if (num>max2){
            max3=max2;
            max2=num;
        }else if(num>max3) {
            max3=num;
        }

        if (max3==-1){
            printf("-1\n");
        }else{
            int prdt=max1*max2*max3;
            printf("%d\n",prdt);
        }
    }
    return 0;
}