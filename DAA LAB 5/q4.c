#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Function to heapify a subtree rooted with node i
// n is the size of the heap
void heapify(int arr[], int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // left child index
    int right = 2 * i + 2; // right child index

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to perform Heap Sort
void heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    int n = 100; // Change this value to handle a larger value of N if needed
    int *arr = (int*)malloc(n * sizeof(int));
    
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize random number generator seed
    srand(time(NULL));

    // 1. Generate N random numbers and write to "random_inputs.txt"
    FILE *fin = fopen("random_inputs.txt", "w");
    if (fin == NULL) {
        printf("Error creating input file!\n");
        free(arr);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fin, "%d\n", rand() % 10000); // Random numbers between 0 and 9999
    }
    fclose(fin);

    // 2. Read the random numbers from "random_inputs.txt" into the array
    FILE *fout = fopen("random_inputs.txt", "r");
    if (fout == NULL) {
        printf("Error opening input file!\n");
        free(arr);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fscanf(fout, "%d", &arr[i]);
    }
    fclose(fout);

    // 3. Perform Heap Sort on the array
    heapSort(arr, n);

    // 4. Write the sorted elements into "heapsort_output.txt"
    FILE *fres = fopen("heapsort_output.txt", "w");
    if (fres == NULL) {
        printf("Error creating output file!\n");
        free(arr);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fres, "%d\n", arr[i]);
    }
    fclose(fres);

    printf("Heap Sort successful! Values saved to 'heapsort_output.txt'.\n");

    // Clean up allocated memory
    free(arr);
    return 0;
}