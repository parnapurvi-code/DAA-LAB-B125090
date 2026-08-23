#include <stdio.h>
#include <string.h>

typedef struct {
    int number;
    char colour[10]; // "red", "blue", "yellow"
} Item;

void sortByColour(Item items[], int n) {
    Item reds[n], blues[n], yellows[n];
    int r = 0, b = 0, y = 0;

    // Distribute items into colour groups
    for (int i = 0; i < n; i++) {
        if (strcmp(items[i].colour, "red") == 0)
            reds[r++] = items[i];
        else if (strcmp(items[i].colour, "blue") == 0)
            blues[b++] = items[i];
        else if (strcmp(items[i].colour, "yellow") == 0)
            yellows[y++] = items[i];
    }

    // Concatenate back into original array
    int idx = 0;
    for (int i = 0; i < r; i++) items[idx++] = reds[i];
    for (int i = 0; i < b; i++) items[idx++] = blues[i];
    for (int i = 0; i < y; i++) items[idx++] = yellows[i];
}

int main() {
    int n;
    printf("Enter number of items: ");
    scanf("%d", &n);

    Item items[n];
    printf("Enter items (number colour):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %s", &items[i].number, items[i].colour);
    }

    sortByColour(items, n);

    printf("\nSorted by colour (reds → blues → yellows):\n");
    for (int i = 0; i < n; i++) {
        printf("%d %s\n", items[i].number, items[i].colour);
    }

    return 0;
}
