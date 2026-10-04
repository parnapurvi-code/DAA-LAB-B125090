#include <stdio.h>

long long nextValue(long long n)
{

    if (n % 2 == 0)
        return n / 2;

    return 3 * n + 1;
}

void collatz(long long n)
{

    printf("%lld", n);

    while (n != 1)
    {

        n = nextValue(n);

        printf(" -> %lld", n);
    }

    printf("\n");
}

void analyze(long long a, long long b)
{

    for (long long i = a; i <= b; i++)
    {

        printf("\nStarting value %lld:\n", i);

        collatz(i);
    }
}

int main()
{

    long long a, b;

    printf("Enter interval [a,b]: ");
    scanf("%lld %lld", &a, &b);

    analyze(a, b);

    return 0;
}