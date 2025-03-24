#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main() {
    int i, N = 100000;
    double s = 0.;

    double *a = (double*)malloc(N * sizeof(double));
    double *b = (double*)malloc(N * sizeof(double));

    if (a == NULL || b == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        a[i] = 10.0 + 2 * i;
        b[i] = 20.0 + sin(0.1 * i);
    }

    #pragma omp parallel for reduction(+:s)
    for (i = 0; i < N - 1; i++) {
        s += a[i];
        a[i + 1] = cos(b[i]);
    }

    printf("Final sum: %f\n", s);

    free(a);
    free(b);

    return 0;
}
