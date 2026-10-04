#include <stdio.h>

#define MAX 20
#define INF 999999

int main()
{
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    int key[MAX];
    float p[MAX];
    float q[MAX];

    float cost[MAX][MAX];
    float weight[MAX][MAX];
    int root[MAX][MAX];

    printf("Enter keys:\n");
    for (int i = 1; i <= n; i++)
        scanf("%d", &key[i]);

    printf("Enter successful probabilities p1 to pn:\n");
    for (int i = 1; i <= n; i++)
        scanf("%f", &p[i]);

    printf("Enter unsuccessful probabilities q0 to qn:\n");
    for (int i = 0; i <= n; i++)
        scanf("%f", &q[i]);

    // Empty subtrees
    for (int i = 1; i <= n + 1; i++)
    {
        cost[i][i - 1] = q[i - 1];
        weight[i][i - 1] = q[i - 1];
    }

    // Build larger subtrees
    for (int length = 1; length <= n; length++)
    {

        for (int i = 1; i <= n - length + 1; i++)
        {

            int j = i + length - 1;

            weight[i][j] = weight[i][j - 1] + p[j] + q[j];

            cost[i][j] = INF;

            for (int r = i; r <= j; r++)
            {

                float current =
                    cost[i][r - 1] + cost[r + 1][j] + weight[i][j];

                if (current < cost[i][j])
                {
                    cost[i][j] = current;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum expected cost = %.2f\n", cost[1][n]);

    printf("Root key = %d\n", key[root[1][n]]);

    return 0;
}