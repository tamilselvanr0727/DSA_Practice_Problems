#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) return 1;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    int left = 0;
    int right = n - 1;
    int first_output = 1;
    while (left < n && right >= 0) {
        if (!first_output) {
            printf(" ");
        }
        first_output = 0;
        if (arr[left] > arr[right]) {
            printf("1");
            right--;  
        } else if (arr[left] < arr[right]) {
            printf("2");
            left++;   
        } else {
            printf("0");
            left++;  
            right--;
        }
    }
    printf("\n");
    free(arr);
    return 0;
}