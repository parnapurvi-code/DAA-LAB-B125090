#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int parent[MAXN], rankArr[MAXN];

// DSU find
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// DSU union
void unionSet(int u, int v) {
    int ru = find(u);
    int rv = find(v);
    if (ru == rv) return;
    if (rankArr[ru] < rankArr[rv]) {
        parent[ru] = rv;
    } else if (rankArr[ru] > rankArr[rv]) {
        parent[rv] = ru;
    } else {
        parent[rv] = ru;
        rankArr[ru]++;
    }
}

int cmpInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    printf("Enter n: ");
    scanf("%d", &n);

    int A[MAXN];
    printf("Enter permutation A: ");
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unionSet(u, v);
    }

    // Group indices by component
    int compId[MAXN];
    for (int i = 0; i < n; i++) compId[i] = find(i);

    // For each component, collect indices and values
    int used[MAXN] = {0};
    for (int i = 0; i < n; i++) {
        if (!used[compId[i]]) {
            used[compId[i]] = 1;

            // Collect indices and values
            int indices[MAXN], values[MAXN];
            int idxCount = 0, valCount = 0;
            for (int j = 0; j < n; j++) {
                if (compId[j] == compId[i]) {
                    indices[idxCount++] = j;
                    values[valCount++] = A[j];
                }
            }

            // Sort indices and values
            qsort(indices, idxCount, sizeof(int), cmpInt);
            qsort(values, valCount, sizeof(int), cmpInt);

            // Assign smallest values to smallest indices
            for (int k = 0; k < idxCount; k++) {
                A[indices[k]] = values[k];
            }
        }
    }

    printf("Lexicographically smallest permutation:\n");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");

    return 0;
}
