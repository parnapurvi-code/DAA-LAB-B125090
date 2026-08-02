#include <stdio.h>

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

    printf("Increasing order of growth for sufficiently large n:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d. %s\n", i + 1, funcs[i].name);
    }

    return 0;
}
