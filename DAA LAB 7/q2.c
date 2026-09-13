#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/*
 * Returns the minimum number of drops required
 * in the worst case using E eggs and F floors.
 */
int eggDrop(int E, int F)
{
    int **dp;

    /*
     * Allocate DP table.
     * dp[e][f] = minimum drops using
     * e eggs and f floors.
     */
    dp = (int **)malloc((E + 1) * sizeof(int *));

    for (int e = 0; e <= E; e++)
    {
        dp[e] = (int *)malloc((F + 1) * sizeof(int));
    }


    /*
     * Base cases
     */

    // Zero floors require zero drops.
    for (int e = 0; e <= E; e++)
        dp[e][0] = 0;

    // One floor requires one drop.
    for (int e = 1; e <= E; e++)
        dp[e][1] = 1;

    // With one egg, test every floor sequentially.
    for (int f = 0; f <= F; f++)
        dp[1][f] = f;


    /*
     * Fill the DP table.
     */
    for (int e = 2; e <= E; e++)
    {
        for (int f = 2; f <= F; f++)
        {
            dp[e][f] = F + 1;

            /*
             * Try dropping from every floor x.
             */
            for (int x = 1; x <= f; x++)
            {
                int breakCase =
                    dp[e - 1][x - 1];

                int surviveCase =
                    dp[e][f - x];

                int worstCase =
                    MAX(breakCase, surviveCase);

                int drops =
                    1 + worstCase;

                dp[e][f] =
                    MIN(dp[e][f], drops);
            }
        }
    }


    int answer = dp[E][F];


    /*
     * Free memory.
     */
    for (int e = 0; e <= E; e++)
        free(dp[e]);

    free(dp);

    return answer;
}


int main()
{
    int E, F;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    if (E <= 0 || F < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    int result = eggDrop(E, F);

    printf("\nMinimum number of droppings = %d\n",
           result);

    return 0;
}