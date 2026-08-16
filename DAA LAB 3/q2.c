#include <stdio.h>

int weigh(int coins[], int a[], int n1, int b[], int n2)
{
    int sumA = 0, sumB = 0;

    for (int i = 0; i < n1; i++)
        sumA += coins[a[i]];

    for (int i = 0; i < n2; i++)
        sumB += coins[b[i]];

    if (sumA < sumB)
        return -1;       // A is lighter
    else if (sumA > sumB)
        return 1;        // B is lighter
    else
        return 0;        // Equal
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter weights of coins:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Coin %d: ", i + 1);
        scanf("%d", &coins[i]);
    }

    /*
       First divide coins into two equal groups.
    */
    int half = n / 2;

    int left[half];
    int right[half];

    for (int i = 0; i < half; i++)
    {
        left[i] = i;
        right[i] = i + half;
    }

    int result = weigh(coins, left, half, right, half);

    /*
       Candidate coins are stored here.
    */
    int candidate[n];
    int candidateCount = 0;

    int goodCoin;

    if (result == -1)
    {
        // Left side is lighter
        for (int i = 0; i < half; i++)
            candidate[candidateCount++] = left[i];

        goodCoin = right[0];
    }
    else if (result == 1)
    {
        // Right side is lighter
        for (int i = 0; i < half; i++)
            candidate[candidateCount++] = right[i];

        goodCoin = left[0];
    }
    else
    {
        /*
           Both sides are equal.
           Therefore all coins in left and right are good.

           If n is odd, the remaining coin is the only
           possible defective coin.
        */
        if (n % 2 == 1)
        {
            candidate[0] = n - 1;
            candidateCount = 1;
            goodCoin = left[0];
        }
        else
        {
            // All coins are good
            printf("\nNo defective coin.\n");
            return 0;
        }
    }

    /*
       Divide-and-conquer search.
    */
    while (candidateCount > 1)
    {
        int halfCandidates = candidateCount / 2;

        int a[halfCandidates];
        int good[halfCandidates];

        for (int i = 0; i < halfCandidates; i++)
        {
            a[i] = candidate[i];
            good[i] = goodCoin;
        }

        int r = weigh(coins, a, halfCandidates,
                      good, halfCandidates);

        if (r == -1)
        {
            // First half contains defective coin
            candidateCount = halfCandidates;
        }
        else
        {
            // Second half contains defective coin
            for (int i = 0; i < candidateCount - halfCandidates; i++)
                candidate[i] = candidate[i + halfCandidates];

            candidateCount -= halfCandidates;
        }
    }

    /*
       Check the final candidate.
    */
    int finalCandidate[1] = {candidate[0]};
    int good[1] = {goodCoin};

    if (weigh(coins, finalCandidate, 1, good, 1) == -1)
    {
        printf("\nDefective coin: Coin %d\n",
               candidate[0] + 1);
        printf("Weight: %d\n", coins[candidate[0]]);
    }
    else
    {
        printf("\nNo defective coin.\n");
    }

    return 0;
}