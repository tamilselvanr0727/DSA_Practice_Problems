#include <stdio.h>

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

int swapArr(int arr[],int n){
    for (int i=0;i<n;i+=2){
        if ((i>0) && (arr[i]<arr[i-1])){
            swap(&arr[i],&arr[i-1]);
        }

        if((i<n-1) && (arr[i]<arr[i+1])){
            swap(&arr[i],&arr[i+1]);
        }
    }
}

void printArr(int arr[],int n){
    for (int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[]={3, 6, 5, 10, 7, 20};
    int n=sizeof(arr)/sizeof(arr[0]);

    printf("Original Array:");
    printArr(arr,n);


    swapArr(arr,n);

    printf("After Swapping:");
    printArr(arr,n);

    return 0;
}