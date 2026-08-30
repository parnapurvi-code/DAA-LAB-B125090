#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function using the last element as pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quicksort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n = 100; // Change this to handle a larger value of N if needed
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

    // 3. Perform Quick Sort on the array
    quickSort(arr, 0, n - 1);

    // 4. Write the sorted elements into "quicksort_output.txt"
    FILE *fres = fopen("quicksort_output.txt", "w");
    if (fres == NULL) {
        printf("Error creating output file!\n");
        free(arr);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fres, "%d\n", arr[i]);
    }
    fclose(fres);

    printf("Quick Sort successful! Values saved to 'quicksort_output.txt'.\n");

    // Clean up allocated memory
    free(arr);
    return 0;
}