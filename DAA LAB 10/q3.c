#include <stdio.h>
#include <stdlib.h>

#define MAXV 1000   // maximum number of vertices

int parent[MAXV], rankArr[MAXV];
int compSize[MAXV], compWeight[MAXV];
int vertexWeight[MAXV];

// DSU find with path compression
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// DSU union by rank, updating size and weight
void unionSet(int u, int v) {
    int ru = find(u);
    int rv = find(v);
    if (ru == rv) return;

    if (rankArr[ru] < rankArr[rv]) {
        parent[ru] = rv;
        compSize[rv] += compSize[ru];
        compWeight[rv] += compWeight[ru];
    } else if (rankArr[ru] > rankArr[rv]) {
        parent[rv] = ru;
        compSize[ru] += compSize[rv];
        compWeight[ru] += compWeight[rv];
    } else {
        parent[rv] = ru;
        compSize[ru] += compSize[rv];
        compWeight[ru] += compWeight[rv];
        rankArr[ru]++;
    }
}

// Compute maximum weight among components with size <= K
int maxWeightComponent(int V, int K) {
    int maxW = 0;
    for (int i = 0; i < V; i++) {
        if (parent[i] == i && compSize[i] <= K) {
            if (compWeight[i] > maxW)
                maxW = compWeight[i];
        }
    }
    return maxW;
}

int main() {
    int V, E, K;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter vertex weights: ");
    for (int i = 0; i < V; i++) {
        scanf("%d", &vertexWeight[i]);
        parent[i] = i;
        rankArr[i] = 0;
        compSize[i] = 1;
        compWeight[i] = vertexWeight[i];
    }

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter size threshold K: ");
    scanf("%d", &K);

    for (int i = 0; i < E; i++) {
        int u, v;
        printf("Enter edge %d (u v): ", i+1);
        scanf("%d %d", &u, &v);

        unionSet(u, v);
        int ans = maxWeightComponent(V, K);
        printf("After edge %d: Max weight component (size <= %d) = %d\n", i+1, K, ans);
    }

    return 0;
}
