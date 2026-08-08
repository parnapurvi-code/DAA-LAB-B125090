#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare_ints(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

// Merge two sorted arrays
void mergeArrays(int *A, int n1, int *B, int n2, int *C) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (A[i] <= B[j]) C[k++] = A[i++];
        else C[k++] = B[j++];
    }
    while (i < n1) C[k++] = A[i++];
    while (j < n2) C[k++] = B[j++];
}

// Method 1: Sequential merging
int* sequentialMerge(int **arrays, int k, int n) {
    int *result = malloc(n * sizeof(int));
    for (int i=0; i<n; i++) result[i] = arrays[0][i];
    int size = n;

    for (int i=1; i<k; i++) {
        int *temp = malloc((size+n) * sizeof(int));
        mergeArrays(result, size, arrays[i], n, temp);
        free(result);
        result = temp;
        size += n;
    }
    return result;
}

// Method 2: Pairwise merging
int* pairwiseMerge(int **arrays, int k, int n) {
    int *sizes = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) sizes[i] = n;

    while (k > 1) {
        int newK = (k + 1) / 2;
        int **newArrays = malloc(newK * sizeof(int*));
        int *newSizes = malloc(newK * sizeof(int));
        int idx = 0;

        for (int i = 0; i < newK; i++) {
            if (idx + 1 < k) {
                newSizes[i] = sizes[idx] + sizes[idx + 1];
                newArrays[i] = malloc(newSizes[i] * sizeof(int));
                mergeArrays(arrays[idx], sizes[idx], arrays[idx + 1], sizes[idx + 1], newArrays[i]);
                free(arrays[idx]);
                free(arrays[idx + 1]);
                idx += 2;
            } else {
                newArrays[i] = arrays[idx];
                newSizes[i] = sizes[idx];
                idx += 1;
            }
        }

        free(arrays);
        free(sizes);
        arrays = newArrays;
        sizes = newSizes;
        k = newK;
    }

    int *result = arrays[0];
    free(arrays);
    free(sizes);
    return result;
}

int main() {
    int k = 8, n = 1000;
    int **arrays = malloc(k * sizeof(int*));
    srand(time(NULL));
    for (int i = 0; i < k; i++) {
        arrays[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arrays[i][j] = rand();
        qsort(arrays[i], n, sizeof(int), compare_ints);
    }

    clock_t start = clock();
    int *res1 = sequentialMerge(arrays, k, n);
    clock_t end = clock();
    printf("Sequential Merge Time: %.6f sec\n", (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    int *res2 = pairwiseMerge(arrays, k, n);
    end = clock();
    printf("Pairwise Merge Time: %.6f sec\n", (double)(end-start)/CLOCKS_PER_SEC);

    free(res1);
    free(res2);
    return 0;
}
