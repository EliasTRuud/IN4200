#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {

    // by default C is organized by rows, so looping over columns fill be slower.
    // Loop over the rows first. Arr [rows][cols], arr[i][j]
    // test it by nested loop
    int rows = 2000;
    int cols = 2000;

    int **matrixA;
    matrixA = (int **)malloc(rows * sizeof(int *));
    matrixA[0] = (int *)malloc(rows * cols * sizeof(int));

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    // This would then be running over each row? meaning faster
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            matrixA[i][j] = (i + j);
        }
    }
    end = clock();
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;

    printf("Time used loop1: %.3f\n", cpu_time_used);

    start = clock();
    // run over cols first?
    for (int j = 0; j < cols; j++){
        for (int i = 0; i < rows; i++){
            matrixA[i][j] = (i + j);
        }
    }
    end = clock();
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;

    printf("Time used loop2: %.3f", cpu_time_used);

    return 0;

    






}