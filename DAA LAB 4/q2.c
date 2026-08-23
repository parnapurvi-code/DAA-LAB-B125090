#include <stdio.h>
#include <stdlib.h>

// Compare function for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Binary search in a sorted array
int binarySearch(int arr[], int n, int key)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return 1;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

// Checks whether any pair from S1 and S2 sums to x
int existsPairSum(int S1[], int S2[], int n, int x)
{
    // Sort S2 so that we can use binary search
    qsort(S2, n, sizeof(int), compare);

    for (int i = 0; i < n; i++)
    {
        int target = x - S1[i];
        if (binarySearch(S2, n, target))
            return 1;
    }

    return 0;
}

int main()
{
    int n, x;

    printf("Enter n: ");
    scanf("%d", &n);

    int S1[n], S2[n];

    printf("Enter %d elements of S1:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &S1[i]);

    printf("Enter %d elements of S2:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &S2[i]);

    printf("Enter x: ");
    scanf("%d", &x);

    if (existsPairSum(S1, S2, n, x))
        printf("YES: There exists a pair, one from S1 and one from S2, whose sum is %d.\n", x);
    else
        printf("NO: No such pair exists.\n");

    return 0;
}
