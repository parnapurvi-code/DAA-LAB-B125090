#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dist;
    int fuel;
} Station;

int cmp(const void *a, const void *b) {
    Station *x = (Station*)a;
    Station *y = (Station*)b;
    return x->dist - y->dist;
}

// Max heap for fuel
void push(int heap[], int *size, int val) {
    int i = (*size)++;
    heap[i] = val;
    while (i > 0 && heap[(i-1)/2] < heap[i]) {
        int tmp = heap[i];
        heap[i] = heap[(i-1)/2];
        heap[(i-1)/2] = tmp;
        i = (i-1)/2;
    }
}

int pop(int heap[], int *size) {
    if (*size == 0) return 0;
    int root = heap[0];
    heap[0] = heap[--(*size)];
    int i = 0;
    while (1) {
        int l = 2*i+1, r = 2*i+2, largest = i;
        if (l < *size && heap[l] > heap[largest]) largest = l;
        if (r < *size && heap[r] > heap[largest]) largest = r;
        if (largest == i) break;
        int tmp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = tmp;
        i = largest;
    }
    return root;
}

int minRefuelStops(int target, int startFuel, Station stations[], int n) {
    qsort(stations, n, sizeof(Station), cmp);
    int heap[n], heapSize = 0;
    int fuel = startFuel, stops = 0, i = 0;

    while (fuel < target) {
        while (i < n && stations[i].dist <= fuel) {
            push(heap, &heapSize, stations[i].fuel);
            i++;
        }
        if (heapSize == 0) return -1; // cannot reach
        fuel += pop(heap, &heapSize);
        stops++;
    }
    return stops;
}

int main() {
    int D = 100, F = 10;
    Station stations[] = {{10,60},{20,30},{30,30},{60,40}};
    int n = sizeof(stations)/sizeof(stations[0]);

    int result = minRefuelStops(D, F, stations, n);
    if (result == -1)
        printf("Cannot reach the target.\n");
    else
        printf("Minimum refuelling stops: %d\n", result);

    return 0;
}
