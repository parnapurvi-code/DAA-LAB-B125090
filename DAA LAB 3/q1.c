#include <stdio.h>
int binarySearch(int arr[], int n, int x) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // Not found
}
int ternarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        if (arr[mid1] == x)
            return mid1;
        if (arr[mid2] == x)
            return mid2;

        if (x < arr[mid1])
            right = mid1 - 1;
        else if (x > arr[mid2])
            left = mid2 + 1;
        else {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    return -1; // Not found
}
int main() {
    int n, x;
    printf("Enter size of sorted array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &x);

    // Binary Search
    int resultBinary = binarySearch(arr, n, x);
    if (resultBinary != -1)
        printf("Binary Search: Element found at index %d\n", resultBinary);
    else
        printf("Binary Search: Element not found\n");

    // Ternary Search
    int resultTernary = ternarySearch(arr, 0, n - 1, x);
    if (resultTernary != -1)
        printf("Ternary Search: Element found at index %d\n", resultTernary);
    else
        printf("Ternary Search: Element not found\n");

    return 0;
}