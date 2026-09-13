#include <stdio.h>

int moveCount = 0;

/* Classical 3-peg Tower of Hanoi */
void hanoi3(int n, char from, char aux, char to) {
    if (n == 0) return;
    hanoi3(n - 1, from, to, aux);
    moveCount++;
    printf("Move disk %d from %c to %c\n", n, from, to);
    hanoi3(n - 1, aux, from, to);
}

/* Frame-Stewart 4-peg algorithm */
void hanoi4(int n, char from, char aux1, char aux2, char to, int k) {
    if (n == 0) return;
    if (n == 1) {
        moveCount++;
        printf("Move disk %d from %c to %c\n", n, from, to);
        return;
    }
    if (n <= 3) { 
        /* small cases: 3-peg is optimal enough, or use base directly */
        hanoi4(n - 1, from, aux2, to, aux1, k);
        moveCount++;
        printf("Move disk %d from %c to %c\n", n, from, to);
        hanoi4(n - 1, aux1, from, aux2, to, k);
        return;
    }
    /* Step 1: move top k disks from 'from' to 'aux1' using 4 pegs */
    hanoi4(k, from, aux2, to, aux1, k);
    /* Step 2: move remaining n-k disks from 'from' to 'to' using 3 pegs */
    hanoi3(n - k, from, aux2, to);
    /* Step 3: move k disks from 'aux1' to 'to' using 4 pegs */
    hanoi4(k, aux1, from, aux2, to, k);
}

int main() {
    int n = 8;
    int k = 3; /* optimal split for n = 8 */
    printf("Solving %d-disk Tower of Hanoi with 4 pegs:\n\n", n);
    hanoi4(n, 'S', 'A', 'B', 'D', k);
    printf("\nTotal moves = %d\n", moveCount);
    return 0;
}