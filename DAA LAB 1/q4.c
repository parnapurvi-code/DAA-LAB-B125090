/*. Towers of Hanoi (ToH): Simulate the solution to the ToH problem using C.
 Plot the total number of moves required for solving the problem of n-discs.
  What can you conclude about your algorithm from the plot obtained*/

#include <stdio.h>
#include <math.h>

void TOH(int n, int source, int temp, int dest)
{
  if (n == 1)
  {
    printf("Move disk 1 from %c to %c\n", source, dest);
    return 0;
  }
  TOH(n - 1, source, dest, temp);
  printf("Move disk %d fro  %c to %c \n", n, source, dest);
  TOH(n - 1, temp, source, dest);
}
int main()
{
  int n;
  printf("Enter the number of disks:\n");
  scanf("%d", &n);
  TOH(n, 'l', 'm', 'r');
  printf("The total moves =%0.1f\n", pow(2, n) - 1);
  return 0;
}