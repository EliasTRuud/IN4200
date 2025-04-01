#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"


int main(void) {
    //char filename[] = "simple.txt";
    //char filename[] = "100.txt";
    char filename[] ="notredame.txt";
    int N;


    // set N depending on filename: https://www.w3schools.com/c/ref_string_strcmp.php , 0 if matches
    if (strcmp(filename, "simple.txt") == 0) {
        N = 8;
    } else if (strcmp(filename, "100.txt") == 0) {
        N = 100;
    } else if (strcmp(filename, "notredame.txt") == 0) {
        N = 325729;
        //N = 200; //temp
    } else {
        printf("Unknown file name: %s\n", filename);
        return 1;
    }
    
    double epsilon = 1e-6;
    double d = 0.85;

    // Method 2: CRS method
    printf("\n\nCRS method");
    int *ptr_ = createArray_int(N+1); //add +1
    double *vals = createArray(N);
    int *idx_ = createArray_int(N);

    read_graph_from_file2(filename, &N, &ptr_, &idx_, &vals);

    // Use parameters from earlier for eps and d
    int n = 5; //pages to print
    double *scores2 = createArray(N);
    PageRank_iterations2_omp(N, ptr_, idx_, vals, d, epsilon, scores2);
    top_n_webpages_omp(N, scores2, n);

    free(scores2);
    free(ptr_);
    free(idx_);
    free(vals);

    return 0;
}
