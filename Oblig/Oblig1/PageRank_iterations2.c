#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void PageRank_iterations2(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores) {
    // Mostly same as page_rank_iterations1, just change in calculating using row_ptr and col_idx
    double *x_old = malloc(N * sizeof(double));
    double *x_new = malloc(N * sizeof(double));

    //init x_old to uniform vector 1/N
    for (int i = 0; i < N; i++) {
        x_old[i] = 1.0 / N;
    }

    int iteration = 0;
    double diff = epsilon + 10.0;  // ensure we enter the loop

    // Perform iterations until convergence, helped with gpt as i encountered lots of errors with indexing first attempts.
    while (diff >= epsilon) {
        double teleport = (1.0 - d) / N; 
        // x_new based on PageRank formula
        for (int i = 0; i < N; i++) {
            double sum = 0.0;
            for (int k = row_ptr[i]; k < row_ptr[i+1]; k++) {
                int j = col_idx[k];
                sum += val[k] * x_old[j];
            }
            x_new[i] = teleport + d * sum;
        }
        // compute max difference between x_new and x_old
        diff = 0.0;
        for (int i = 0; i < N; i++) {
            double delta = fabs(x_new[i] - x_old[i]);
            if (delta > diff)
                diff = delta;
        }
        // Copy x_new into x_old
        for (int i = 0; i < N; i++) {
            x_old[i] = x_new[i];
        }
        iteration++;
    }
    // Copy final values into scores array
    for (int i = 0; i < N; i++) {
        scores[i] = x_old[i];
    }
    free(x_old);
    free(x_new);
}
