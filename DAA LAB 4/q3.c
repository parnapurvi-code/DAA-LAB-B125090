#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int cmp(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

// Binary search
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return 1;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}

// Recursive k-sum function
int kSum(int S[], int n, int k, int T) {
    // Base case: two-sum
    if (k == 2) {
        for (int i = 0; i < n; i++) {
            int complement = T - S[i];
            if (binarySearch(S, n, complement)) {
                return 1;
            }
        }
        return 0;
    }

    // Recursive case: fix one element and reduce problem
    for (int i = 0; i < n; i++) {
        if (kSum(S, n, k-1, T - S[i])) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int S[] = {1, 2, 4, 5, 7};
    int n = 5, T = 12, k = 3;

    qsort(S, n, sizeof(int), cmp);  // sort array

    if (kSum(S, n, k, T))
        printf("%d-sum exists for target %d\n", k, T);
    else
        printf("No %d-sum found for target %d\n", k, T);

    return 0;
}
