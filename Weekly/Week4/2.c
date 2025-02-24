
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(){

    // Just used square matrices. Look for weekly solutions for proper code


    int rows = 2, cols = 2;

    // Allocate memory for the 2D Aay (Aay of pointers to rows)
    double **A = (double **)malloc(rows * sizeof(double *));
    double **B = (double **)malloc(rows * sizeof(double *));
    double **C = (double **)malloc(rows * sizeof(double *));
    double **D = (double **)malloc(rows * sizeof(double *));
    
    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        A[i] = (double *)malloc(cols * sizeof(double));
        B[i] = (double *)malloc(cols * sizeof(double));
        C[i] = (double *)malloc(cols * sizeof(double));
        D[i] = (double *)malloc(cols * sizeof(double));
    }

    // initialize A and B
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            A[i][j] = i + j;
            B[i][j] = (i+3) + (j+1);
        }
    }

    // Mat multiplication
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            C[i][j] = 0;
            for (int k = 0; k < cols; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }  

    //Loop unrolling mat mult
    

    //Print C
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f ", C[i][j]);
        }
        printf("\n");
    }


    //Print D
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f ", D[i][j]);
        }
        printf("\n");
    }

    free(A);free(B);free(C);free(D);

    return 0;
}