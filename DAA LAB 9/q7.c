#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *arr;
    int size;
} MaxHeap;

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void heapify(MaxHeap *heap, int i) {
    int largest = i;
    int l = 2*i+1, r = 2*i+2;
    if (l < heap->size && heap->arr[l] > heap->arr[largest]) largest = l;
    if (r < heap->size && heap->arr[r] > heap->arr[largest]) largest = r;
    if (largest != i) {
        swap(&heap->arr[i], &heap->arr[largest]);
        heapify(heap, largest);
    }
}

int extractMax(MaxHeap *heap) {
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    heapify(heap, 0);
    return root;
}

void insertHeap(MaxHeap *heap, int val) {
    int i = heap->size++;
    heap->arr[i] = val;
    while (i > 0 && heap->arr[(i-1)/2] < heap->arr[i]) {
        swap(&heap->arr[i], &heap->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

int minimumDeviation(int nums[], int n) {
    MaxHeap heap;
    heap.arr = (int*)malloc(n * 20 * sizeof(int)); // enough space
    heap.size = 0;

    int minVal = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (nums[i] % 2 == 1) nums[i] *= 2; // normalize to even
        insertHeap(&heap, nums[i]);
        if (nums[i] < minVal) minVal = nums[i];
    }

    int deviation = INT_MAX;
    while (heap.size > 0) {
        int maxVal = extractMax(&heap);
        if (maxVal - minVal < deviation) deviation = maxVal - minVal;
        if (maxVal % 2 == 0) {
            maxVal /= 2;
            if (maxVal < minVal) minVal = maxVal;
            insertHeap(&heap, maxVal);
        } else {
            break;
        }
    }

    free(heap.arr);
    return deviation;
}

int main() {
    int nums[] = {1,2,3,4};
    int n = sizeof(nums)/sizeof(nums[0]);
    int result = minimumDeviation(nums, n);
    printf("Minimum deviation: %d\n", result);
    return 0;
}
