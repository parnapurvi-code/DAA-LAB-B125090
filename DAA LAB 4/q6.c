#include <stdio.h>
#include <stdlib.h>

struct Event {
    int point;
    int type; // +1 for start, -1 for end
};

// Comparator for qsort
int cmp(const void *a, const void *b) {
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;
    if (e1->point == e2->point)
        return e2->type - e1->type; // entry (+1) before exit (-1)
    return e1->point - e2->point;
}

int main() {
    int n;
    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Event events[2*n];
    printf("Enter intervals (li ri):\n");
    for (int i = 0; i < n; i++) {
        int li, ri;
        scanf("%d %d", &li, &ri);
        events[2*i].point = li;
        events[2*i].type = +1; // start
        events[2*i+1].point = ri;
        events[2*i+1].type = -1; // end
    }

    // Sort events
    qsort(events, 2*n, sizeof(struct Event), cmp);

    int current = 0, maxCover = 0, bestPoint = -1;

    for (int i = 0; i < 2*n; i++) {
        current += events[i].type;
        if (current > maxCover) {
            maxCover = current;
            bestPoint = events[i].point;
        }
    }

    printf("\nPoint with maximum overlap = %d\n", bestPoint);
    printf("Maximum intervals covering it = %d\n", maxCover);

    return 0;
}
