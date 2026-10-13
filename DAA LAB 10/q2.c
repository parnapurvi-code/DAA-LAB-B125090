#include <stdio.h>
#include <stdlib.h>

#define MAXRC 10000   // maximum R*C

int parent[MAXRC], rankArr[MAXRC];
int isLand[MAXRC];

// DSU find with path compression
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// DSU union by rank
int unionSet(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx == ry) return 0; // already connected

    if (rankArr[rx] < rankArr[ry]) {
        parent[rx] = ry;
    } else if (rankArr[rx] > rankArr[ry]) {
        parent[ry] = rx;
    } else {
        parent[ry] = rx;
        rankArr[rx]++;
    }
    return 1; // merged successfully
}

int main() {
    int R, C, K;
    printf("Enter grid size R C: ");
    scanf("%d %d", &R, &C);

    int total = R * C;
    for (int i = 0; i < total; i++) {
        parent[i] = i;
        rankArr[i] = 0;
        isLand[i] = 0;
    }

    printf("Enter number of operations: ");
    scanf("%d", &K);

    int islands = 0;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    for (int k = 0; k < K; k++) {
        int r, c;
        printf("Enter land position %d (r c): ", k+1);
        scanf("%d %d", &r, &c);

        int idx = r * C + c;
        if (isLand[idx]) {
            printf("Already land. Islands = %d\n", islands);
            continue;
        }

        isLand[idx] = 1;
        islands++;

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            int nidx = nr * C + nc;
            if (isLand[nidx]) {
                if (unionSet(idx, nidx)) {
                    islands--; // merged two islands
                }
            }
        }

        printf("After operation %d: Islands = %d\n", k+1, islands);
    }

    return 0;
}
