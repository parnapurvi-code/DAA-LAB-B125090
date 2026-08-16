#include <stdio.h>

void selectionSort(int A[], int n)
{
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;

        for (j = i + 1; j < n; j++)
        {
            if (A[j] < A[min])
            {
                min = j;
            }
        }

        /* Exchange A[i] and A[min] */
        temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }
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

    selectionSort(A, n);

    printf("\nSorted array:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }

    printf("\n");

    return 0;
}