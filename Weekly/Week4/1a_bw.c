
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "week4.h" //can store all our functions in that file instead.
int main(){
    int N = 1000;
    int s = 2;

    double *A = malloc(N * sizeof(double));
    double *B = malloc(N * sizeof(double));

    for(int i=0; i<N; i++){
        B[i] = i*2;
    }

    clock_t start = clock();
    for(int i=0; i<N; i++){
        A[i] = s*B[i];
    }
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;

    int stride = 32;
    clock_t start2 = clock();
    for (int i=0; i<N; i+=stride){
        A[i] = s*B[i];
    }
    clock_t end2 = clock();
    float seconds_2 = (float)(end2 - start2) / CLOCKS_PER_SEC;

    double n_bytes = 2*N*sizeof(double);
    double n_bytes_2 = n_bytes/stride;

    double bandwidth = n_bytes / seconds;
    double bandwidth_2 = n_bytes_2 / seconds_2;
    printf("Mem bandwidth: %.2e bytes per sec\n", bandwidth);
    printf("Mem bandwidth for stride: %.2e bytes per sec\n", bandwidth_2); 
    //not cache friendly way, we load the same amount but just do less FLOPS, so less bandwidth when strides.
    /*
    Large Strides (stride = 128, 256, 1024, etc.)

        Lower bandwidth: The CPU accesses scattered locations, reducing cache efficiency.
        Fewer FLOPS: More cache misses lead to higher memory latency, slowing down computation.
    */
    free(A); free(B);
    return 0;
}