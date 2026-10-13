#include <stdio.h>
#include <stdlib.h>

#define MAXV 1000
#define MAXE 2000

int parent[MAXV], rankArr[MAXV], compWeight[MAXV], active[MAXV];
int vertexWeight[MAXV];

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
        compWeight[rv] += compWeight[ru];
    } else if (rankArr[ru] > rankArr[rv]) {
        parent[rv] = ru;
        compWeight[ru] += compWeight[rv];
    } else {
        parent[rv] = ru;
        compWeight[ru] += compWeight[rv];
        rankArr[ru]++;
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter vertex weights: ");
    for (int i = 0; i < V; i++) {
        scanf("%d", &vertexWeight[i]);
        parent[i] = i;
        rankArr[i] = 0;
        compWeight[i] = 0;
        active[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &E);

    int edges[MAXE][2];
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }

    int P[MAXV];
    printf("Enter deletion order of vertices: ");
    for (int i = 0; i < V; i++) {
        scanf("%d", &P[i]);
    }

    int result[MAXV];
    int maxComp = 0;

    // Process in reverse
    for (int i = V-1; i >= 0; i--) {
        int v = P[i];
        active[v] = 1;
        compWeight[v] = vertexWeight[v];
        parent[v] = v;
        rankArr[v] = 0;

        // Connect to active neighbors
        for (int j = 0; j < E; j++) {
            int u = edges[j][0], w = edges[j][1];
            if (u == v && active[w]) unionSet(u, w);
            if (w == v && active[u]) unionSet(w, u);
        }

        // Update max component weight
        int root = find(v);
        if (compWeight[root] > maxComp)
            maxComp = compWeight[root];

        result[i] = maxComp;
    }

    // Print results in forward deletion order
    printf("Maximum component weights after each deletion:\n");
    for (int i = 0; i < V; i++) {
        printf("After deleting %d: %d\n", P[i], result[i]);
    }

    return 0;
}
