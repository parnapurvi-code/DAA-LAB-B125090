#include <stdio.h>
#include <string.h>

int min(int a, int b, int c)
{
    if (a < b && a < c)
        return a;
    if (b < c)
        return b;
    return c;
}

int main()
{
    char A[100], B[100];

    printf("Enter string A: ");
    scanf("%s", A);

    printf("Enter string B: ");
    scanf("%s", B);

    int m = strlen(A);
    int n = strlen(B);

    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {

            if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1];

            else
                dp[i][j] = 1 + min(
                                   dp[i][j - 1],    // insertion
                                   dp[i - 1][j],    // deletion
                                   dp[i - 1][j - 1] // substitution
                               );
        }
    }

    printf("Edit Distance = %d\n", dp[m][n]);

    // Traceback
    int i = m;
    int j = n;

    printf("\nOperations:\n");

    while (i > 0 || j > 0)
    {

        if (i > 0 && j > 0 && A[i - 1] == B[j - 1])
        {
            i--;
            j--;
        }

        else if (i > 0 && j > 0 &&
                 dp[i][j] == dp[i - 1][j - 1] + 1)
        {

            printf("Substitute %c with %c\n",
                   A[i - 1], B[j - 1]);

            i--;
            j--;
        }

        else if (i > 0 &&
                 dp[i][j] == dp[i - 1][j] + 1)
        {

            printf("Delete %c\n", A[i - 1]);

            i--;
        }

        else
        {

            printf("Insert %c\n", B[j - 1]);

            j--;
        }
    }

    return 0;
}