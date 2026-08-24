#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CONSTANT,
    SQRT,
    POWER_051,
    LINEAR,
    LINEAR_LOG,
    QUADRATIC,
    CUBIC
} GrowthType;

typedef struct {
    const char *name;
    GrowthType type;
} Function;

// Comparison function for qsort
int compareFunctions(const void *a, const void *b) {
    const Function *fa = (const Function *)a;
    const Function *fb = (const Function *)b;
    return (fa->type - fb->type);
}

int main(void) {
    Function funcs[] = {
        {"1", CONSTANT},
        {"12√n", SQRT},
        {"50n^0.5", SQRT},
        {"n^0.51", POWER_051},
        {"3n", LINEAR},
        {"nlog2 n", LINEAR_LOG},
        {"232n log2 n", LINEAR_LOG},
        {"n^2 - 324", QUADRATIC},
        {"100n^2 + 6n", QUADRATIC},
        {"2n^3", CUBIC}
    };

    int n = sizeof(funcs) / sizeof(funcs[0]);

    // Sort the array by growth type
    qsort(funcs, n, sizeof(Function), compareFunctions);

    printf("Increasing order of growth for sufficiently large n:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i + 1, funcs[i].name);
    }

    return 0;
}

