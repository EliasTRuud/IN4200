#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"


int main(void) {
    char filename[] = "simple.txt";
    //char filename[] = "100.txt";
    //char filename[] ="notredame.txt";
    int N;
    int n = 6; //pages to print of top pages
    double epsilon = 1e-6;
    double d = 0.85;


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
    
    // Dense matrix
    printf("Dense matrix method");
    double **linkmat  = createMatrix2D(N);
    read_graph_from_file1(filename, &N, &linkmat);
    //printf("Link Matrix (%d x %d):\n", N, N);
    //printMatrix2D(linkmat, N);
    //freeMatrix2D(linkmat, N);

    // Algorithm for dense matrix versionn
    double *scores = createArray(N);
    PageRank_iterations1(N, linkmat, d, epsilon, scores);
    
    top_n_webpages(N, scores, n);
    
    freeMatrix2D(linkmat, N);
    free(scores);

    //*************************************************************** *

    // Method 2: CRS method
    printf("\n\nCRS method");
    int *ptr_ = createArray_int(N+1); //add +1
    double *vals = createArray(N);
    int *idx_ = createArray_int(N);

    read_graph_from_file2(filename, &N, &ptr_, &idx_, &vals);

    // Use parameters from earlier for eps and d
    double *scores2 = createArray(N);
    PageRank_iterations2(N, ptr_, idx_, vals, d, epsilon, scores2);

    //print top pasges
    top_n_webpages(N, scores2, n);
    free(scores2);
    free(ptr_);
    free(idx_);
    free(vals);


    //*************************************************************** *

    // Method 2: CRS method, testing large file
    printf("\n\nCRS method: big file");
    char filename2[] = "notredame.txt";
    N = 325729;
    //N = 1000;
    int *ptr_2 = createArray_int(N+1); //add +1
    double *vals2 = createArray(N);
    int *idx_2 = createArray_int(N);

    read_graph_from_file2(filename2, &N, &ptr_2, &idx_2, &vals2);

    // Use parameters from earlier for eps and d
    double *scores3 = createArray(N);
    PageRank_iterations2(N, ptr_2, idx_2, vals2, d, epsilon, scores3);

    //print top pasges
    top_n_webpages(N, scores3, n);
    
    free(scores3);
    free(ptr_2);
    free(idx_2);
    free(vals2);

    return 0;
}
