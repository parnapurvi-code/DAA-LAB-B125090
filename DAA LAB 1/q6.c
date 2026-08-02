/*Element uniqueness:: For given n random numbers, implement a method in C to check if there are any duplicates. What can you conclude about your method for a sufficiently large value of n?*/

#include <stdio.h>
int main()
{
    int n;
    printf("Enter value of n:\n");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &n);
    }

    int dup = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                dup = 1;
                break;
            }
        }
        if (dup)
            break;
    }

    if (dup)
        printf("Duplicate elem found\n");
    else
        printf("Duplicate elem not found\n");
    return 0;
}