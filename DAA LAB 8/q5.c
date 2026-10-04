#include <stdio.h>

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int a[n], dp[n];

    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < n; i++)
        dp[i] = a[i];

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {

            if (a[j] < a[i] && dp[j] + a[i] > dp[i])
                dp[i] = dp[j] + a[i];
        }
    }

    int max = dp[0];

    for (int i = 1; i < n; i++)
    {
        if (dp[i] > max)
            max = dp[i];
    }

    printf("Maximum sum = %d\n", max);

    return 0;
}