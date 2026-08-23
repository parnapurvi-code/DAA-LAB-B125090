#include <stdio.h>
#include <stdlib.h>

struct Event {
    int time;
    int type; // +1 for entry, -1 for exit
};

// Comparator for qsort
int cmp(const void *a, const void *b) {
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;
    return e1->time - e2->time;
}

int main() {
    int n;
    printf("Enter number of persons: ");
    scanf("%d", &n);

    struct Event events[2*n];

    printf("Enter entry and exit times (ai bi):\n");
    for (int i = 0; i < n; i++) {
        int ai, bi;
        scanf("%d %d", &ai, &bi);
        events[2*i].time = ai;
        events[2*i].type = +1; // entry
        events[2*i+1].time = bi;
        events[2*i+1].type = -1; // exit
    }

    // Sort events by time
    qsort(events, 2*n, sizeof(struct Event), cmp);

    int current = 0, maxPeople = 0, maxTime = -1;

    for (int i = 0; i < 2*n; i++) {
        current += events[i].type;
        if (current > maxPeople) {
            maxPeople = current;
            maxTime = events[i].time;
        }
    }

    printf("\nMaximum people present = %d at time %d\n", maxPeople, maxTime);

    return 0;
}
