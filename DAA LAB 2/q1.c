#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ------------------ Structures ------------------
typedef struct Node {
    int key;
    struct Node *next;
    struct Node *prev; // used only for doubly linked lists
} Node;

// ------------------ Utility ------------------
double getTime(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// ------------------ Unsorted Array ------------------
int search_unsorted_array(int arr[], int n, int k) {
    for (int i = 0; i < n; i++) if (arr[i] == k) return i;
    return -1;
}
void insert_unsorted_array(int arr[], int *n, int x) {
    arr[(*n)++] = x;
}
void delete_unsorted_array(int arr[], int *n, int idx) {
    if (idx >= 0 && idx < *n) {
        arr[idx] = arr[*n - 1];
        (*n)--;
    }
}
int max_unsorted_array(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    return max;
}
int min_unsorted_array(int arr[], int n) {
    int min = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] < min) min = arr[i];
    return min;
}

// ------------------ Sorted Array ------------------
int search_sorted_array(int arr[], int n, int k) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] == k) return mid;
        else if (arr[mid] < k) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}
void insert_sorted_array(int arr[], int *n, int x) {
    int i = *n - 1;
    while (i >= 0 && arr[i] > x) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = x;
    (*n)++;
}
void delete_sorted_array(int arr[], int *n, int idx) {
    if (idx >= 0 && idx < *n) {
        for (int i = idx; i < *n - 1; i++) arr[i] = arr[i + 1];
        (*n)--;
    }
}
int max_sorted_array(int arr[], int n) { return arr[n - 1]; }
int min_sorted_array(int arr[], int n) { return arr[0]; }

// ------------------ Linked Lists ------------------
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->next = node->prev = NULL;
    return node;
}

// Insert unsorted singly linked list
void insert_unsorted_sll(Node **head, int x) {
    Node *node = newNode(x);
    node->next = *head;
    *head = node;
}
int search_unsorted_sll(Node *head, int k) {
    while (head) {
        if (head->key == k) return 1;
        head = head->next;
    }
    return 0;
}
void delete_unsorted_sll(Node **head, int k) {
    Node *curr = *head, *prev = NULL;
    while (curr) {
        if (curr->key == k) {
            if (prev) prev->next = curr->next;
            else *head = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// ------------------ Experiment Driver ------------------
void run_experiment(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    int size = 0;

    clock_t start, end;

    // Insert unsorted array
    start = clock();
    for (int i = 0; i < n; i++) insert_unsorted_array(arr, &size, rand());
    end = clock();
    printf("Unsorted Array Insert n=%d time=%f\n", n, getTime(start, end));

    // Search unsorted array
    start = clock();
    for (int i = 0; i < n; i++) search_unsorted_array(arr, size, rand());
    end = clock();
    printf("Unsorted Array Search n=%d time=%f\n", n, getTime(start, end));

    free(arr);
}

// ------------------ Main ------------------
int main() {
    srand(time(NULL));
    int sizes[] = {1000, 2000, 5000, 10000};
    int numSizes = sizeof(sizes)/sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        run_experiment(sizes[i]);
    }

    return 0;
}
