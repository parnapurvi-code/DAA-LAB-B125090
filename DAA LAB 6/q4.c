#include <stdio.h>
#include <stdlib.h>

long long totalCost = 0;
long long reversalCount = 0;

/* Reverse p[l...r]
   Positions are 0-based.
*/
void reverseRange(int p[], int l, int r)
{
    if (l >= r)
        return;

    int length = r - l + 1;

    int i = l;
    int j = r;

    while (i < j)
    {
        int temp = p[i];
        p[i] = p[j];
        p[j] = temp;

        i++;
        j--;
    }

    reversalCount++;
    totalCost += length;
}

/*
    Find the first element > pivot.

    Since partition() guarantees:
        <= pivot | > pivot

    this gives the boundary between the two groups.
*/
int findBoundary(int p[], int l, int r, int pivot)
{
    int i = l;

    while (i <= r && p[i] <= pivot)
        i++;

    return i;
}

/*
    Partition p[l...r] into:

        values <= pivot | values > pivot

    using only reversals.

    Returns the first position of the
    values > pivot section.
*/
int partitionByValue(int p[], int l, int r, int pivot)
{
    if (l == r)
    {
        if (p[l] <= pivot)
            return l + 1;
        else
            return l;
    }

    int mid = (l + r) / 2;

    /* Divide */
    partitionByValue(p, l, mid, pivot);
    partitionByValue(p, mid + 1, r, pivot);

    /*
        After recursive calls:

        [small | large] [small | large]

        We need:

        [small small] [large large]
    */

    int leftBoundary =
        findBoundary(p, l, mid, pivot);

    int rightBoundary =
        findBoundary(p, mid + 1, r, pivot);

    /*
        Middle section:

        [leftBoundary ... mid]       = large
        [mid+1 ... rightBoundary-1]  = small

        Rotate them using 3 reversals:

        X Y -> Y X
    */

    int xStart = leftBoundary;
    int xEnd = mid;

    int yStart = mid + 1;
    int yEnd = rightBoundary - 1;

    if (xStart <= xEnd && yStart <= yEnd)
    {
        /* Reverse X */
        reverseRange(p, xStart, xEnd);

        /* Reverse Y */
        reverseRange(p, yStart, yEnd);

        /* Reverse XY */
        reverseRange(p, xStart, yEnd);
    }

    /*
        Find new boundary.

        All values <= pivot are now before
        all values > pivot.
    */
    return findBoundary(p, l, r, pivot);
}

/*
    Divide-and-conquer sorting.

    Values in p[l...r] are assumed to be
    exactly low...high.
*/
void reversalSort(int p[], int l, int r,
                  int low, int high)
{
    /* Base case */
    if (low >= high || l >= r)
        return;

    int pivot = (low + high) / 2;

    /*
        Partition by value:

        low ... pivot | pivot+1 ... high
    */
    int boundary =
        partitionByValue(p, l, r, pivot);

    /*
        Number of elements in the left group
        tells us where to recursively sort.
    */
    int leftSize = boundary - l;

    /*
        Recursively sort both groups.
    */
    if (leftSize > 0)
    {
        reversalSort(p,
                     l,
                     boundary - 1,
                     low,
                     pivot);
    }

    if (boundary <= r)
    {
        reversalSort(p,
                     boundary,
                     r,
                     pivot + 1,
                     high);
    }
}

/* Check whether array is sorted */
int isSorted(int p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (p[i] != i + 1)
            return 0;
    }

    return 1;
}

/* Print permutation */
void printArray(int p[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int *p = malloc(n * sizeof(int));

    printf("Enter permutation of 1 to %d:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("\nOriginal permutation:\n");
    printArray(p, n);

    /*
        Sort using reversal-based
        divide-and-conquer algorithm.
    */
    reversalSort(p, 0, n - 1, 1, n);

    printf("\nSorted permutation:\n");
    printArray(p, n);

    printf("\nNumber of reversals = %lld\n",
           reversalCount);

    printf("Total reversal cost = %lld\n",
           totalCost);

    if (isSorted(p, n))
        printf("Verification: SORTED\n");
    else
        printf("Verification: NOT SORTED\n");

    free(p);

    return 0;
}