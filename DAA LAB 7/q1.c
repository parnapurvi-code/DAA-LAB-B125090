#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
    int x;
    int y;
} Point;


/* Check whether two points are equal */
int samePoint(Point a, Point b)
{
    return a.x == b.x && a.y == b.y;
}


/* Check whether a point exists in an array */
int contains(Point arr[], int size, Point p)
{
    for (int i = 0; i < size; i++)
    {
        if (samePoint(arr[i], p))
            return 1;
    }

    return 0;
}


/*
 * Generate the original upright triangle.
 *
 * Row 0 :        O
 * Row 1 :       O O
 * Row 2 :      O O O
 * ...
 */
int generateOriginal(Point coins[], int n)
{
    int count = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col <= row; col++)
        {
            coins[count].x = 2 * col - row;
            coins[count].y = row;

            count++;
        }
    }

    return count;
}


/*
 * Generate the inverted triangle.
 *
 * dx and dy determine where the inverted triangle
 * is placed relative to the original triangle.
 */
int generateInverted(Point target[], int n, int dx, int dy)
{
    int count = 0;

    for (int row = 0; row < n; row++)
    {
        int coinsInRow = n - row;

        for (int col = 0; col < coinsInRow; col++)
        {
            target[count].x =
                dx + 2 * col - (coinsInRow - 1);

            target[count].y =
                dy + row;

            count++;
        }
    }

    return count;
}


/*
 * Find the best position of the inverted triangle.
 *
 * The optimal placement can be selected according
 * to n modulo 3.
 */
void getOptimalShift(int n, int *dx, int *dy)
{
    if (n % 3 == 1)
    {
        *dx = 0;
        *dy = (n - 1) / 3;
    }
    else
    {
        *dx = -1;
        *dy = n / 3;
    }
}


/*
 * Print the current arrangement.
 *
 * '#' = coin
 * '.' = empty position
 */
void printBoard(Point coins[], int coinCount,
                int n, int dx, int dy)
{
    int minX = -n - 3;
    int maxX = n + 3;
    int minY = 0;
    int maxY = n + dy + 1;

    printf("\033[H\033[J");

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            Point p = {x, y};

            if (contains(coins, coinCount, p))
            {
                printf("O ");
            }
            else
            {
                printf("  ");
            }
        }

        printf("\n");
    }

    printf("\n");
}


/* Pause for animation */
void pauseAnimation(void)
{
    usleep(500000);
}


int main(void)
{
    int n;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of rows must be positive.\n");
        return 1;
    }


    /*
     * Total number of coins:
     *
     * n(n+1)/2
     */
    int totalCoins = n * (n + 1) / 2;


    /*
     * Allocate memory for coins.
     */
    Point *coins =
        malloc(totalCoins * sizeof(Point));

    Point *target =
        malloc(totalCoins * sizeof(Point));

    if (coins == NULL || target == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }


    /*
     * Generate original triangle.
     */
    int coinCount =
        generateOriginal(coins, n);


    /*
     * Find optimal position for inverted triangle.
     */
    int dx, dy;

    getOptimalShift(n, &dx, &dy);


    /*
     * Generate final inverted triangle.
     */
    int targetCount =
        generateInverted(target, n, dx, dy);


    printf("\nInitial triangle:\n");
    printBoard(coins, coinCount, n, dx, dy);

    pauseAnimation();


    /*
     * Move every coin that is not already
     * in its final position.
     */
    int moves = 0;

    for (int i = 0; i < coinCount; i++)
    {
        /*
         * If this coin is already in a target
         * position, leave it there.
         */
        if (contains(target, targetCount, coins[i]))
            continue;


        /*
         * Find an empty target position.
         *
         * A target position is empty if no current
         * coin occupies it.
         */
        for (int j = 0; j < targetCount; j++)
        {
            if (!contains(coins, coinCount, target[j]))
            {
                printf("Move %d: (%d,%d) -> (%d,%d)\n",
                       moves + 1,
                       coins[i].x,
                       coins[i].y,
                       target[j].x,
                       target[j].y);

                /*
                 * Move the coin.
                 */
                coins[i] = target[j];

                moves++;

                printBoard(coins, coinCount,
                           n, dx, dy);

                pauseAnimation();

                break;
            }
        }
    }


    printf("\nFinal inverted triangle:\n");

    printBoard(coins, coinCount, n, dx, dy);

    printf("Minimum moves = %d\n", moves);

    printf("Formula = floor(n(n+1)/6)\n");
    printf("Expected = %d\n",
           n * (n + 1) / 6);


    free(coins);
    free(target);

    return 0;
}