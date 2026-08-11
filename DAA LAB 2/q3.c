#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

    int currK = k;
    int **currArrays = malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) currArrays[i] = arrays[i];
    int *currSizes = sizes;

    while (currK > 1) {
        int newK = (currK + 1) / 2;
        int **newArrays = malloc(newK * sizeof(int*));
        int *newSizes = malloc(newK * sizeof(int));
        int idx = 0;

        for (int i = 0; i < newK; i++) {
            if (idx + 1 < currK) {
                newSizes[i] = currSizes[idx] + currSizes[idx + 1];
                newArrays[i] = malloc(newSizes[i] * sizeof(int));
                mergeArrays(currArrays[idx], currSizes[idx], currArrays[idx + 1], currSizes[idx + 1], newArrays[i]);
                idx += 2;
            } else {
                newSizes[i] = currSizes[idx];
                newArrays[i] = malloc(newSizes[i] * sizeof(int));
                memcpy(newArrays[i], currArrays[idx], newSizes[i] * sizeof(int));
                idx += 1;
            }
        }

        free(currArrays);
        free(currSizes);
        currArrays = newArrays;
        currSizes = newSizes;
        currK = newK;
    }

    int *result = currArrays[0];
    free(currArrays);
    free(currSizes);
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
    /* free original input arrays */
    for (int i = 0; i < k; i++) free(arrays[i]);
    free(arrays);

    free(res1);
    free(res2);
    return 0;
}
