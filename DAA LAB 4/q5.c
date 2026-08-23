#include <stdio.h>
#include <stdlib.h>

struct Interval {
    int start, end;
};

// Comparator for qsort
int cmp(const void *a, const void *b) {
    struct Interval *i1 = (struct Interval *)a;
    struct Interval *i2 = (struct Interval *)b;
    return i1->start - i2->start;
}

int main() {
    int n;
    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Interval intervals[n];
    printf("Enter intervals (xi yi):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    // Sort intervals by start time
    qsort(intervals, n, sizeof(struct Interval), cmp);

    printf("\nMerged intervals:\n");
    int currentStart = intervals[0].start;
    int currentEnd = intervals[0].end;

    for (int i = 1; i < n; i++) {
        if (intervals[i].start <= currentEnd) {
            // Overlap → extend
            if (intervals[i].end > currentEnd)
                currentEnd = intervals[i].end;
        } else {
            // No overlap → output current
            printf("(%d,%d) ", currentStart, currentEnd);
            currentStart = intervals[i].start;
            currentEnd = intervals[i].end;
        }
    }
    // Print last interval
    printf("(%d,%d)\n", currentStart, currentEnd);

    return 0;
}
