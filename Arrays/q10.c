#include <stdio.h>

int main(){
    int t;
    if (scanf("%d",&t)!=1) return 0;

    while (t){
        int n;
        scanf("%d",&n);

        int sizes[n];
        for (int i=0;i<n;i++){
            scanf("%d",&sizes[i]);
        }

        int treat=0;
        for (int i=0;i<n;i++){
            int unique=0;
            for (int j=0;j<n;j++){
                if (sizes[j]<sizes[i]){
                    int count=0;
                    for (int k=0;k<j;k++){
                        if (sizes[k]==sizes[j]){
                            count=1;
                            break;
                        }
                    }
                    if (!count){
                        unique++;
                    }
                }
            }
            treat+=(1+unique);
        }
        printf("%d\n",treat);
        t--;
    }
    return 0;
}