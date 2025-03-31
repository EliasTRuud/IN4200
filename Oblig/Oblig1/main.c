#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"


int main(void) {
    char filename[] = "simple.txt";
    //char filename[] = "100.txt";
    //char filename[] ="notredame.txt";
    int N;


    // set N depending on filename: https://www.w3schools.com/c/ref_string_strcmp.php , 0 if matches
    if (strcmp(filename, "simple.txt") == 0) {
        N = 8;
    } else if (strcmp(filename, "100.txt") == 0) {
        N = 100;
    } else if (strcmp(filename, "notredame.txt") == 0) {
        //N = 325729;
        N = 200; //temp
    } else {
        printf("Unknown file name: %s\n", filename);
        return 1;
    }
    /*
    // make linkmatrix
    double **linkmat  = createMatrix2D(N);

    read_graph_from_file1(filename, &N, &linkmat);

    printf("Link Matrix (%d x %d):\n", N, N);
    printMatrix2D(linkmat, N);
    //freeMatrix2D(linkmat, N);


    double epsilon = 1e-6;
    double d = 0.85;
    double *scores = malloc(N * sizeof(double));

    PageRank_iterations1(N, linkmat, d, epsilon, scores);
    
    // Print the PageRank scores
    printf("PageRank scores:\n");
    for(int i = 0; i < N; i++){
        printf("%f ", scores[i]);
    }
    printf("\n");
    
    freeMatrix2D(linkmat, N);
    free(scores);

    */

    // Method 2: CRS method

    int *ptr_ = createArray_int(N+1); //add +1
    double *vals = createArray(N);
    int *idx_ = createArray_int(N);

    read_graph_from_file2(filename, &N, &ptr_, &idx_, &vals);

    printArray_int(ptr_, N);
    printArray(vals, N);
    printArray_int(idx_, N);
    


    return 0;
}
