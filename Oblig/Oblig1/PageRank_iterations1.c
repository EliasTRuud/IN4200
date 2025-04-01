#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcs.h"

void PageRank_iterations1(int N, double **hyperlink_matrix, double d, double epsilon, double *scores) {
    double *x_old = malloc(N * sizeof(double));
    double *x_new = malloc(N * sizeof(double));
    
    // divide by N
    for (int i = 0; i < N; i++) {
        x_old[i] = 1.0 / N;
    }
    
    int iteration = 0;
    double diff = epsilon + 10;  // ensure we enter the loop
    double W; //is sum from dangling pages corresponding to the curr x elements
    
    while (diff >= epsilon) {
        W = 0.0;
        // sum scores of dangling pages (pages with all zero in their col)
        for (int j = 0; j < N; j++) {
            int isDangling = 1;
            for (int i = 0; i < N; i++) {
                if (hyperlink_matrix[i][j] != 0.0) {
                    isDangling = 0;
                    break;
                }
            }
            if (isDangling) {
                W += x_old[j];
            }
        }
        
        //term (1-d + d*W)/N
        double teleport = (1.0 - d + d * W) / N;
        
        // compute new pagerank vector: x_new = term + d * (A * x_old)
        for (int i = 0; i < N; i++) {
            double sum = 0.0;
            for (int j = 0; j < N; j++) {
                sum += hyperlink_matrix[i][j] * x_old[j];
            }
            x_new[i] = teleport + d * sum;
        }
        
        // calc max absolute diff between x_new and x_old
        diff = 0.0;
        for (int i = 0; i < N; i++) {
            double delta = fabs(x_new[i] - x_old[i]);
            if (delta > diff) {
                diff = delta;
            }
        }
        
        // copy x_new into x_old for next iteration
        for (int i = 0; i < N; i++) {
            x_old[i] = x_new[i];
        }
        
        iteration++;

    }
    
    // copy final pagerank scores into provided scores array
    for (int i = 0; i < N; i++) {
        scores[i] = x_old[i];
    }


    free(x_old);
    free(x_new);
}
