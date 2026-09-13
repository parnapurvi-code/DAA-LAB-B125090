#include <stdio.h>

int n;
int shots = 0;

void shoot(int pos, int *targetPos, int *targetDir) {
    shots++;
    printf("Shot %d: check position %d\n", shots, pos);
    if (pos == *targetPos) {
        printf("HIT! Target found at position %d after %d shots.\n", pos, shots);
        return;
    }
    /* simulate target forced move to adjacent spot */
    if (*targetPos == 1) *targetDir = 1;
    else if (*targetPos == n) *targetDir = -1;
    *targetPos += *targetDir;
}

int main() {
    printf("Enter number of hiding spots (n): ");
    scanf("%d", &n);

    int targetPos, targetDir = 1;
    printf("Enter target's actual starting position (1..%d) [hidden from shooter]: ", n);
    scanf("%d", &targetPos);

    int hit = 0;
    /* Forward sweep: 2..n-1 */
    for (int i = 2; i <= n - 1 && !hit; i++) {
        if (i == targetPos) hit = 1;
        shoot(i, &targetPos, &targetDir);
        if (i == targetPos) { hit = 1; }
    }
    /* Backward sweep: n-1..2 */
    for (int i = n - 1; i >= 2 && !hit; i--) {
        if (i == targetPos) hit = 1;
        shoot(i, &targetPos, &targetDir);
        if (i == targetPos) { hit = 1; }
    }

    if (!hit)
        printf("Target not hit (check parity logic / edge cases for small n).\n");

    printf("\nTotal shots fired = %d\n", shots);
    return 0;
}