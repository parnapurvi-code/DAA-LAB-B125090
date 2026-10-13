#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ch;
    int freq;
} Node;

typedef struct {
    Node *arr;
    int size;
} MaxHeap;

void swap(Node *a, Node *b) {
    Node t = *a; *a = *b; *b = t;
}

void heapify(MaxHeap *heap, int i) {
    int largest = i;
    int l = 2*i+1, r = 2*i+2;
    if (l < heap->size && heap->arr[l].freq > heap->arr[largest].freq) largest = l;
    if (r < heap->size && heap->arr[r].freq > heap->arr[largest].freq) largest = r;
    if (largest != i) {
        swap(&heap->arr[i], &heap->arr[largest]);
        heapify(heap, largest);
    }
}

Node extractMax(MaxHeap *heap) {
    Node root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    heapify(heap, 0);
    return root;
}

void insertHeap(MaxHeap *heap, Node node) {
    int i = heap->size++;
    heap->arr[i] = node;
    while (i > 0 && heap->arr[(i-1)/2].freq < heap->arr[i].freq) {
        swap(&heap->arr[i], &heap->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

char* reorganizeString(char *s, int k) {
    int n = strlen(s);
    if (k <= 1) return s;

    int freq[256] = {0};
    for (int i = 0; i < n; i++) freq[(int)s[i]]++;

    MaxHeap heap;
    heap.arr = (Node*)malloc(256 * sizeof(Node));
    heap.size = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            Node node = {(char)i, freq[i]};
            insertHeap(&heap, node);
        }
    }

    char *result = (char*)malloc((n+1) * sizeof(char));
    int idx = 0;

    Node waitQueue[256];
    int front = 0, rear = 0;

    while (heap.size > 0) {
        Node curr = extractMax(&heap);
        result[idx++] = curr.ch;
        curr.freq--;

        waitQueue[rear++] = curr;
        if (rear - front >= k) {
            Node frontNode = waitQueue[front++];
            if (frontNode.freq > 0) insertHeap(&heap, frontNode);
        }
    }

    result[idx] = '\0';
    if (idx == n) return result;
    free(result);
    return "";
}

int main() {
    char s[] = "aabbcc";
    int k = 3;
    char *res = reorganizeString(s, k);
    if (strlen(res) == 0)
        printf("Impossible to rearrange.\n");
    else
        printf("Reorganized string: %s\n", res);
    return 0;
}
