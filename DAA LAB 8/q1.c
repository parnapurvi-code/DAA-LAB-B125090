#include <stdio.h>

#define INF 99999

int main()
{
    int n, V;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coin[n];

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &coin[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    int dp[V + 1];

    dp[0] = 0;

    for (int i = 1; i <= V; i++)
        dp[i] = INF;

    for (int i = 1; i <= V; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if (coin[j] <= i && dp[i - coin[j]] != INF)
            {
                if (dp[i - coin[j]] + 1 < dp[i])
                    dp[i] = dp[i - coin[j]] + 1;
            }
        }
    }

    if (dp[V] == INF)
        printf("Cannot make the target amount\n");
    else
        printf("Minimum number of coins = %d\n", dp[V]);

    return 0;
}