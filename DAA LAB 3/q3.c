#include <stdio.h>

int comparisons = 0;

/* Structure to store minimum and maximum */
struct Result {
    int min;
    int max;
};

/* Divide and Conquer function */
struct Result findMinMax(int A[], int low, int high)
{
    struct Result left, right, result;

    /* Case 1: Only one element */
    if (low == high)
    {
        result.min = A[low];
        result.max = A[low];

        return result;
    }

    /* Case 2: Two elements */
    if (high == low + 1)
    {
        comparisons++;

        if (A[low] < A[high])
        {
            result.min = A[low];
            result.max = A[high];
        }
        else
        {
            result.min = A[high];
            result.max = A[low];
        }

        return result;
    }

    /* Divide */
    int mid = (low + high) / 2;

    /* Conquer */
    left = findMinMax(A, low, mid);
    right = findMinMax(A, mid + 1, high);

    /* Combine: find minimum */
    comparisons++;

    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    /* Combine: find maximum */
    comparisons++;

    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int A[n];

    printf("Enter the elements:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    struct Result result;

    result = findMinMax(A, 0, n - 1);

    printf("\nMinimum = %d\n", result.min);
    printf("Maximum = %d\n", result.max);
    printf("Number of comparisons = %d\n", comparisons);

    return 0;
}