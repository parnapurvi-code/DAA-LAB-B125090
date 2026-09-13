#include <stdio.h>

int sw[100];       // 1 = ON, 0 = OFF
int n;
long moveCount = 0;

void toggle(int pos) {
    sw[pos] = !sw[pos];
    moveCount++;
    printf("Move %ld: Toggle switch %d -> %s\n", moveCount, pos, sw[pos] ? "ON" : "OFF");
}

/* Recursively turns OFF switches 1..k, given switch k+1 (if exists) is ON 
   and everything right of k+1 is OFF (loop invariant maintained). */
void turnOff(int k) {
    if (k == 0) return;
    if (k == 1) {
        toggle(1);
        return;
    }
    turnOff(k - 1);      // clear switches 1..k-1 (switch k stays as is)
    toggle(k);            // toggle switch k (valid: switch k+1 ON, right of it OFF)
    turnOffToOn(k - 1);   // restore switches 1..k-1 back to ON pattern needed for consistency
}

/* Helper: brings switches 1..k back to ALL ON (mirror process) */
void turnOffToOn(int k) {
    if (k == 0) return;
    if (k == 1) {
        toggle(1);
        return;
    }
    turnOff(k - 1);
    toggle(k);
    turnOffToOn(k - 1);
}

int main() {
    printf("Enter number of switches: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) sw[i] = 1;  // all ON initially

    printf("\nInitial state: all %d switches ON\n\n", n);

    turnOff(n);

    printf("\nFinal state: ");
    for (int i = 1; i <= n; i++) printf("%d", sw[i]);
    printf("\nTotal moves = %ld (Expected: 2^%d - 1 = %ld)\n",
           moveCount, n, (1L << n) - 1);

    return 0;
}