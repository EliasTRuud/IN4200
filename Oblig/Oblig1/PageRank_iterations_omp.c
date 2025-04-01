#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void PageRank_iterations2_omp(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores) {
    //Pretty much the same code, just added three omp for, at the loops.
    double *x_old = malloc(N * sizeof(double));
    double *x_new = malloc(N * sizeof(double));

    //init x_old to uniform vector 1/N
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        x_old[i] = 1.0 / N;
    }

    int iteration = 0;
    double diff = epsilon + 10.0;  // ensure loop is entered

    while (diff >= epsilon) {
        double teleport = (1.0 - d) / N;
        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            double sum = 0.0;
            for (int k = row_ptr[i]; k < row_ptr[i+1]; k++) {
                int j = col_idx[k];
                sum += val[k] * x_old[j];
            }
            x_new[i] = teleport + d * sum;
        }

        // Compute maximum absolute difference between x_new and x_old with reduction
        diff = 0.0;
        #pragma omp parallel for reduction(max:diff)
        for (int i = 0; i < N; i++) {
            double delta = fabs(x_new[i] - x_old[i]);
            if (delta > diff)
                diff = delta;
        }

        // Copy x_new into x_old for the next iteration
        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            x_old[i] = x_new[i];
        }
        iteration++;

    }

    // Copy final pagerank scores into provided scores array
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        scores[i] = x_old[i];
    }

    free(x_old);
    free(x_new);
}
