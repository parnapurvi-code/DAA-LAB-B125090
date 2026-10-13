#include <stdio.h>
#include <stdlib.h>

#define MAXV 1000   // maximum number of vertices

int parent[MAXV], rank[MAXV], parity[MAXV];

// Find with path compression, also update parity
int find(int x) {
    if (parent[x] != x) {
        int root = find(parent[x]);
        parity[x] ^= parity[parent[x]];
        parent[x] = root;
    }
    return parent[x];
}

// Union with parity tracking
int unionSet(int u, int v) {
    int ru = find(u);
    int rv = find(v);

    if (ru == rv) {
        // Same component: check parity
        if (parity[u] == parity[v]) {
            return 0; // odd cycle detected → violates bipartiteness
        }
        return 1; // still bipartite
    }

    // Union by rank
    if (rank[ru] < rank[rv]) {
        parent[ru] = rv;
        parity[ru] = parity[u] ^ parity[v] ^ 1;
    } else if (rank[ru] > rank[rv]) {
        parent[rv] = ru;
        parity[rv] = parity[u] ^ parity[v] ^ 1;
    } else {
        parent[rv] = ru;
        parity[rv] = parity[u] ^ parity[v] ^ 1;
        rank[ru]++;
    }
    return 1;
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    // Initialize DSU
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
        parity[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < E; i++) {
        int u, v;
        printf("Enter edge %d (u v): ", i+1);
        scanf("%d %d", &u, &v);

        if (!unionSet(u, v)) {
            printf("Edge (%d,%d) introduces an odd cycle → violates bipartiteness. Skipped.\n", u, v);
        } else {
            printf("Edge (%d,%d) added. Graph remains bipartite.\n", u, v);
        }
    }

    return 0;
}
