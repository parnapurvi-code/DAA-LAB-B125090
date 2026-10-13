#include <stdio.h>
#include <stdlib.h>

int minCandies(int ratings[], int n) {
    int *candies = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) candies[i] = 1;

    // Left to right
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i-1])
            candies[i] = candies[i-1] + 1;
    }

    // Right to left
    for (int i = n-2; i >= 0; i--) {
        if (ratings[i] > ratings[i+1] && candies[i] <= candies[i+1])
            candies[i] = candies[i+1] + 1;
    }

    int total = 0;
    for (int i = 0; i < n; i++) total += candies[i];
    free(candies);
    return total;
}

int main() {
    int ratings[] = {1, 0, 2};
    int n = sizeof(ratings)/sizeof(ratings[0]);

    int result = minCandies(ratings, n);
    printf("Minimum candies required: %d\n", result);

    return 0;
}
