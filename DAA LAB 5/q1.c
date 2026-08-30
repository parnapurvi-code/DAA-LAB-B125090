#include <stdio.h>
#include <limits.h>
int find_median(int arr[], int n, int idx){
    int count = 1;
    int min = arr[0];
    int id;
    for(int i=0; i<n; i++){
        if (arr[i] < min){
            min = arr[i];
            id = i;
        }
    }
    while(count != idx){
        arr[id] = INT_MAX;
        min = INT_MAX;
        for(int i=0; i<n; i++){
            if (arr[i]<min){
                min = arr[i];
                id = i;
            }
        }
        count++;
        if(count == idx){
            printf("median: %d", min);
            break;
        }
    }
}
int main(){
    int n;
    printf("enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i<n; i++){
        printf("enter any number: ");
        scanf("%d", &arr[i]);
    }
    int idx;
    if (n % 2 == 0){
        idx = n/2;
    }
    else{
        idx = (n/2)+1;
    }
    find_median(arr, n, idx);
    return 0;
}