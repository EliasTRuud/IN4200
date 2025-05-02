#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



void GS_iteration_normal(int kmax, int jmax, int imax, double ***phi) {
    // Default implementation from task
    int k, j, i;

    for (k = 1; k < kmax - 1; k++) {
        for (j = 1; j < jmax - 1; j++) {
            for (i = 1; i < imax - 1; i++) {
                phi[k][j][i] = (phi[k-1][j][i] + phi[k][j-1][i]
                              + phi[k][j][i-1] + phi[k][j][i+1]
                              + phi[k][j+1][i] + phi[k+1][j][i]) / 6.0;
            }
        }
    }
}


void GS_iteration_2_chunks(int kmax, int jmax, int imax, double ***phi) {
    /*
    Serial version. Split up using 2 chunks, split j-direction into left (j=1 -> jmax/2) and right (jmax/2 -> jmax-2)
    */
    int k, j, i;
    int j_m = jmax/2;

    // First wavefront: only computation on left chunk at level k=1
    k = 1;
    for(j=1; j<j_m; j++){
        for (i = 1; i < imax - 1; i++) {
                phi[k][j][i] = (phi[k-1][j][i] + phi[k][j-1][i]
                              + phi[k][j][i-1] + phi[k][j][i+1]
                              + phi[k][j+1][i] + phi[k+1][j][i]) / 6.0;
        }
    }

    for (k = 2; k <= kmax - 2; k++) {
        // Computation on left chunk at level k
        for(j=1; j < j_m; j++){
            for (i = 1; i < imax - 1; i++) {
                phi[k][j][i] = (phi[k-1][j][i] + phi[k][j-1][i]
                              + phi[k][j][i-1] + phi[k][j][i+1]
                              + phi[k][j+1][i] + phi[k+1][j][i]) / 6.0;
            }
        }

        // Computation on right chunk at level k-1
        for(j=j_m; j<jmax-1; j++){
            for (i = 1; i < imax - 1; i++) {
                            phi[k-1][j][i] = (phi[k-2][j][i] + phi[k-1][j-1][i]
                                        + phi[k-1][j][i-1] + phi[k-1][j][i+1]
                                        + phi[k-1][j+1][i] + phi[k][j][i]) / 6.0;
            }
        }
    }

    // Last wavefront: only computation on right chunk at level k=kmax-2
    // ...
    k = kmax-2;
    for(j=j_m; j<jmax-1; j++){
            for (i = 1; i < imax - 1; i++) {
                             phi[k][j][i] = (phi[k-1][j][i] + phi[k][j-1][i]
                              + phi[k][j][i-1] + phi[k][j][i+1]
                              + phi[k][j+1][i] + phi[k+1][j][i]) / 6.0;
            }
        }
}

void allocate_array3D(int kmax, int jmax, int imax, double ****array){
    // Allocate 3d array : array[kmax][jmax][imax]
    double ***arr;
    arr = (double ***) malloc(kmax * sizeof(double**));

    for (int k = 0; k<kmax ; k++){
        arr[k] = (double **) malloc(jmax * sizeof(double*));
        for (int j = 0; j<jmax; j++){
            arr[k][j] = (double*) malloc(imax * sizeof(double));
        }
    }
    *array = arr;

}


double euclidean_distance(int kmax, int jmax, int imax, double ***arr1, double ***arr2){
    // Compute eulidean distance between two 3d arrays. Has to be same dimensions
    // Go through every point, compute difference. Sqaure it, sum it up then finally returns square of the total sum
    // Used to compare results of normal and 2 chunks funcs
    double sum = 0.0;
    double difference;

    for (int k = 0; k < kmax; k++) {
        for (int j = 0; j < jmax; j++) {
            for (int i = 0; i < imax; i++) {
                difference = arr1[k][j][i] - arr2[k][j][i];
                sum += difference * difference;
            }
        }
    }
    return sqrt(sum);
}


void initialize_arrays(int kmax, int jmax, int imax, double ***arr1, double ***arr2) {
    // initalize 2 indentical arrays with values
    int k, j, i;
    
    // Loop through the 3D arrays to fill them with initial values
    for (k = 0; k < kmax; k++) {
        for (j = 0; j < jmax; j++) {
            for (i = 0; i < imax; i++) {
                arr1[k][j][i] = (double)(k + j + i); //sum of indices
                arr2[k][j][i] = (double)(k + j + i);  
            }
        }
    }
}
int main(int nargs, char **args) {
    double ***arr1, ***arr2;
    int n, k, j, i;
    int num_iters, kmax, jmax, imax;

    /*    
    num_iters = 1;
    kmax = 5; jmax = 5; imax = 5;
    */
    
    // Read num_iters, kmax, jmax, and imax from command line
    num_iters = atoi(args[1]);
    kmax = atoi(args[2]);
    jmax = atoi(args[3]);
    imax = atoi(args[4]);

    allocate_array3D(kmax, jmax, imax, &arr1);
    allocate_array3D(kmax, jmax, imax, &arr2);

    // Assign same (non-constant) initial values to arr1 and arr2
    initialize_arrays(kmax, jmax, imax, arr1, arr2);

    for (n = 0; n < num_iters; n++) {
        GS_iteration_normal(kmax, jmax, imax, arr1);
        GS_iteration_2_chunks(kmax, jmax, imax, arr2);
    }

    printf("num iters=%d, kmax=%d, jmax=%d, imax=%d, diff=%g\n",
           num_iters, kmax, jmax, imax,
           euclidean_distance(kmax, jmax, imax, arr1, arr2));

    return 0;
}
