#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000 // Size of the vectors

int main() {
    // Allocate memory for vectors
    double *a = (double*)malloc(N * sizeof(double));
    double *b = (double*)malloc(N * sizeof(double));
    double sum = 0.0;

    // Initialize vectors with some values
    for (int i = 0; i < N; i++) {
        a[i] = 1.0; // Fill with 1s
        b[i] = 2.0; // Fill with 2s
    }

    // Parallelize the loop with different schedules

    // Static scheduling with chunk size 1024
    #pragma omp parallel for reduction(+:sum) schedule(static, 1024)
    for (int i = 0; i < N; i++) {
        sum += a[i] * b[i];
    }

    printf("Sum with static scheduling: %f\n", sum);

    // Reset sum for next scheduling strategy
    sum = 0.0;

    // Dynamic scheduling with chunk size 1024
    #pragma omp parallel for reduction(+:sum) schedule(dynamic, 1024)
    for (int i = 0; i < N; i++) {
        sum += a[i] * b[i];
    }

    printf("Sum with dynamic scheduling: %f\n", sum);

    // Reset sum for next scheduling strategy
    sum = 0.0;

    // Guided scheduling with chunk size 1024
    #pragma omp parallel for reduction(+:sum) schedule(guided, 1024)
    for (int i = 0; i < N; i++) {
        sum += a[i] * b[i];
    }

    printf("Sum with guided scheduling: %f\n", sum);

    // Free allocated memory
    free(a);
    free(b);

    return 0;
}
