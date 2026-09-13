#include <stdio.h>
#include <limits.h>

#define MAX 20

int m[MAX][MAX];   // m[i][j] = min scalar multiplications for Ai..Aj
int s[MAX][MAX];   // s[i][j] = optimal split point

void matrixChainOrder(int p[], int n) {
    // n = number of matrices, p[] has n+1 elements
    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    // L = chain length (number of matrices in the subchain)
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
}

// Print optimal parenthesization recursively
void printOptimalParens(int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(i, s[i][j]);
        printOptimalParens(s[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int n;
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[MAX];
    printf("Enter %d dimensions (p0 p1 ... p%d) such that matrix Ai has dimension p[i-1] x p[i]:\n", n + 1, n);
    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    matrixChainOrder(p, n);

    printf("\nMinimum number of scalar multiplications: %d\n", m[1][n]);

    printf("Optimal Parenthesization: ");
    printOptimalParens(1, n);
    printf("\n");

    // Optional: print the full DP table
    printf("\nDP Table m[i][j]:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i)
                printf("%6s", "-");
            else
                printf("%6d", m[i][j]);
        }
        printf("\n");
    }

    return 0;
}