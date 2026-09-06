#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* (i) Find maximum */
int findMax(int a[], int n)
{
    int max = a[0];

    for (int i = 1; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }

    return max;
}

/* (ii) Find first and second largest */
void findLargestTwo(int a[], int n, int *largest, int *second)
{
    *largest = *second = -999999999;

    for (int i = 0; i < n; i++)
    {
        if (a[i] > *largest)
        {
            *second = *largest;
            *largest = a[i];
        }
        else if (a[i] > *second && a[i] != *largest)
        {
            *second = a[i];
        }
    }
}

/* (iii) Find mean */
double findMean(int a[], int n)
{
    long long sum = 0;

    for (int i = 0; i < n; i++)
        sum += a[i];

    return (double)sum / n;
}

/* Comparison function for qsort */
int compare(const void *x, const void *y)
{
    return (*(int *)x - *(int *)y);
}

/* (iv) Find median */
double findMedian(int a[], int n)
{
    int *temp = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        temp[i] = a[i];

    qsort(temp, n, sizeof(int), compare);

    double median;

    if (n % 2 == 1)
        median = temp[n / 2];
    else
        median = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;

    free(temp);

    return median;
}

/* (v) Find standard deviation */
double findStandardDeviation(int a[], int n)
{
    double mean = findMean(a, n);
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double difference = a[i] - mean;
        sum += difference * difference;
    }

    return sqrt(sum / n);
}

/* (vi) Find mode */
int findMode(int a[], int n)
{
    int mode = a[0];
    int maxCount = 0;

    for (int i = 0; i < n; i++)
    {
        int count = 0;

        for (int j = 0; j < n; j++)
        {
            if (a[i] == a[j])
                count++;
        }

        if (count > maxCount)
        {
            maxCount = count;
            mode = a[i];
        }
    }

    return mode;
}

/* (vii) Remove duplicates */
int removeDuplicates(int a[], int n)
{
    int newSize = 0;

    for (int i = 0; i < n; i++)
    {
        int duplicate = 0;

        for (int j = 0; j < newSize; j++)
        {
            if (a[i] == a[j])
            {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate)
        {
            a[newSize] = a[i];
            newSize++;
        }
    }

    return newSize;
}

/* (viii) Reverse array */
void reverseArray(int a[], int n)
{
    int left = 0;
    int right = n - 1;

    while (left < right)
    {
        int temp = a[left];
        a[left] = a[right];
        a[right] = temp;

        left++;
        right--;
    }
}

/* (ix) Partition with respect to pivot
   Elements >= pivot come before elements < pivot */
void partitionArray(int a[], int n, int pivot)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        while (left <= right && a[left] >= pivot)
            left++;

        while (left <= right && a[right] < pivot)
            right--;

        if (left < right)
        {
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;

            left++;
            right--;
        }
    }
}

/* Print array */
void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\nOriginal array: ");
    printArray(a, n);

    /* (i) Maximum */
    printf("\n(i) Maximum = %d\n", findMax(a, n));

    /* (ii) First and second largest */
    int largest, second;
    findLargestTwo(a, n, &largest, &second);

    printf("(ii) Largest = %d\n", largest);
    printf("     Second largest = %d\n", second);

    /* (iii) Mean */
    printf("\n(iii) Mean = %.2f\n", findMean(a, n));

    /* (iv) Median */
    printf("(iv) Median = %.2f\n", findMedian(a, n));

    /* (v) Standard deviation */
    printf("(v) Standard deviation = %.2f\n",
           findStandardDeviation(a, n));

    /* (vi) Mode */
    printf("(vi) Mode = %d\n", findMode(a, n));

    /* (vii) Remove duplicates */
    int newSize = removeDuplicates(a, n);

    printf("\n(vii) After removing duplicates: ");
    printArray(a, newSize);

    /* (viii) Reverse */
    reverseArray(a, newSize);

    printf("(viii) Reversed array: ");
    printArray(a, newSize);

    /* (ix) Partition */
    int pivot;

    printf("\nEnter pivot: ");
    scanf("%d", &pivot);

    partitionArray(a, newSize, pivot);

    printf("(ix) Partitioned array: ");
    printArray(a, newSize);

    free(a);

    return 0;
}