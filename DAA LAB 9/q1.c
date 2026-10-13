#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double v, w, lambda;
    double rho; // priority score
} Item;

int cmp(const void *a, const void *b) {
    Item *x = (Item*)a;
    Item *y = (Item*)b;
    if (x->rho > y->rho) return -1;
    if (x->rho < y->rho) return 1;
    return 0;
}

int main() {
    int n;
    double W;
    printf("Enter number of items and knapsack capacity: ");
    scanf("%d %lf", &n, &W);

    Item items[n];
    for (int i = 0; i < n; i++) {
        printf("Enter value, weight, decay rate for item %d: ", i+1);
        scanf("%lf %lf %lf", &items[i].v, &items[i].w, &items[i].lambda);
        items[i].rho = (items[i].v / items[i].w) / items[i].lambda;
    }

    qsort(items, n, sizeof(Item), cmp);

    double totalValue = 0.0;
    double remaining = W;

    for (int i = 0; i < n && remaining > 0; i++) {
        if (items[i].w <= remaining) {
            totalValue += items[i].v;
            remaining -= items[i].w;
        } else {
            totalValue += (items[i].v / items[i].w) * remaining;
            remaining = 0;
        }
    }

    printf("Maximum total value: %.4lf\n", totalValue);
    return 0;
}
