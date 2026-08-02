/*Find the partition point: Consider an array A with n elements
 containing a run of 0’s followed by a run of 1’s.
  Implement a method to find out the exact point of transition between them*/

#include <stdio.h>

int part(int nums[], int n)
{
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (nums[mid] == 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

int main()
{
    int n;
    printf("Enter value of n:\n");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elem:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int ans = part(arr, n);

    printf("Partition point=%d\n", ans);
    return 0;
}