#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Standard two-way merge
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Three-way merge
void threeWayMerge(int arr[], int l, int m1, int m2, int r) {
    int n1 = m1 - l + 1, n2 = m2 - m1, n3 = r - m2;
    int A[n1], B[n2], C[n3];
    for (int i = 0; i < n1; i++) A[i] = arr[l + i];
    for (int j = 0; j < n2; j++) B[j] = arr[m1 + 1 + j];
    for (int k = 0; k < n3; k++) C[k] = arr[m2 + 1 + k];

    int i = 0, j = 0, k = 0, idx = l;
    while (i < n1 || j < n2 || k < n3) {
        int minVal = INT_MAX;
        if (i < n1) minVal = (A[i] < minVal) ? A[i] : minVal;
        if (j < n2) minVal = (B[j] < minVal) ? B[j] : minVal;
        if (k < n3) minVal = (C[k] < minVal) ? C[k] : minVal;

        if (i < n1 && A[i] == minVal) arr[idx++] = A[i++];
        else if (j < n2 && B[j] == minVal) arr[idx++] = B[j++];
        else arr[idx++] = C[k++];
    }
}

void modifiedMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int third = (r - l + 1) / 3;
        int m1 = l + third - 1;
        int m2 = l + 2 * third - 1;
        modifiedMergeSort(arr, l, m1);
        modifiedMergeSort(arr, m1 + 1, m2);
        modifiedMergeSort(arr, m2 + 1, r);
        threeWayMerge(arr, l, m1, m2, r);
    }
}

int main() {
    srand(time(NULL));
    int n;
    for (n = 1000; n <= 10000; n += 1000) {
        int *arr1 = malloc(n * sizeof(int));
        int *arr2 = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            int val = rand();
            arr1[i] = val;
            arr2[i] = val;
        }

        clock_t start = clock();
        mergeSort(arr1, 0, n - 1);
        clock_t end = clock();
        double time_merge = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        modifiedMergeSort(arr2, 0, n - 1);
        end = clock();
        double time_modified = (double)(end - start) / CLOCKS_PER_SEC;

        printf("n=%d, MergeSort=%.6f, ModifiedMergeSort=%.6f\n", n, time_merge, time_modified);

        free(arr1);
        free(arr2);
    }
    return 0;
}
