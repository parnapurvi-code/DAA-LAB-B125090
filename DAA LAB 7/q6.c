#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int year;
    int type;   // +1 = birth, -1 = death
} Event;

int compare(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    if (e1->year != e2->year)
        return e1->year - e2->year;
    return e1->type - e2->type;  // -1 (death) before +1 (birth) on tie
}

int main() {
    int n;
    printf("Enter number of scientists: ");
    scanf("%d", &n);

    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    for (int i = 0; i < n; i++) {
        int birth, death;
        printf("Enter birth and death year of scientist %d: ", i + 1);
        scanf("%d %d", &birth, &death);
        events[2*i].year = birth;
        events[2*i].type = 1;
        events[2*i + 1].year = death;
        events[2*i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(Event), compare);

    int count = 0, maxCount = 0, maxYear = 0;
    for (int i = 0; i < 2 * n; i++) {
        count += events[i].type;
        if (count > maxCount) {
            maxCount = count;
            maxYear = events[i].year;
        }
    }

    printf("\nMaximum number of scientists alive at once: %d\n", maxCount);
    printf("This maximum occurs at year: %d\n", maxYear);

    free(events);
    return 0;
}