#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int minMeetingRooms(int intervals[][2], int n) {
    int *start = (int*)malloc(n * sizeof(int));
    int *end = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        start[i] = intervals[i][0];
        end[i] = intervals[i][1];
    }

    qsort(start, n, sizeof(int), cmp);
    qsort(end, n, sizeof(int), cmp);

    int rooms = 0, maxRooms = 0;
    int i = 0, j = 0;

    while (i < n && j < n) {
        if (start[i] < end[j]) {
            rooms++;
            if (rooms > maxRooms) maxRooms = rooms;
            i++;
        } else {
            rooms--;
            j++;
        }
    }

    free(start);
    free(end);
    return maxRooms;
}

int main() {
    int intervals[][2] = {{0,30},{5,10},{15,20}};
    int n = sizeof(intervals)/sizeof(intervals[0]);

    int result = minMeetingRooms(intervals, n);
    printf("Minimum number of meeting rooms required: %d\n", result);

    return 0;
}
