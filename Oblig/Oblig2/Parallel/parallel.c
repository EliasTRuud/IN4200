// File: gs_sendrecv.c

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

/* allocate 3D array [kmax][jmax][imax] */
void allocate_array3D(int kmax, int jmax, int imax, double ****array) {
    double ***arr = malloc(kmax * sizeof(double**));
    for (int k = 0; k < kmax; k++) {
        arr[k] = malloc(jmax * sizeof(double*));
        for (int j = 0; j < jmax; j++) {
            arr[k][j] = malloc(imax * sizeof(double));
        }
    }
    *array = arr;
}

void free_array3D(int kmax, int jmax, double ***arr) {
    for (int k = 0; k < kmax; k++) {
        for (int j = 0; j < jmax; j++) {
            free(arr[k][j]);
        }
        free(arr[k]);
    }
    free(arr);
}

void initialize_array(int kmax, int jmax, int imax, double ***phi) {
    for (int k = 0; k < kmax; k++)
      for (int j = 0; j < jmax; j++)
        for (int i = 0; i < imax; i++)
          phi[k][j][i] = (double)(k + j + i);
}


void GS_iteration_2_chunks_mpi(int my_rank, int kmax, int jmax, int imax, double ***phi) {
    int my_jmax = jmax/2 + 1, j_m = my_jmax - 1, partner = 1 - my_rank;

    if (my_rank == 0)
        for (int j = 1; j < j_m; j++)
            for (int i = 1; i < imax-1; i++)
                phi[1][j][i] = (
                    phi[0][j][i] + phi[1][j-1][i] +
                    phi[1][j][i-1] + phi[1][j][i+1] +
                    phi[1][j+1][i] + phi[2][j][i]
                ) / 6.0;
    
    // chatgpt helped with this portion to use Sendrecv and its paramaters in this case.
    for (int k = 2; k <= kmax-2; k++) {
        if (my_rank == 0) {
            for (int j = 1; j < j_m; j++)
                for (int i = 1; i < imax-1; i++)
                    phi[k][j][i] = (
                        phi[k-1][j][i] + phi[k][j-1][i] +
                        phi[k][j][i-1] + phi[k][j][i+1] +
                        phi[k][j+1][i] + phi[k+1][j][i]
                    ) / 6.0;
            
            MPI_Sendrecv(&phi[k][j_m-1][1], imax-2, MPI_DOUBLE, partner, k,
                         &phi[k-1][j_m][1], imax-2, MPI_DOUBLE, partner, k,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        else {
            MPI_Sendrecv(&phi[k-1][1][1], imax-2, MPI_DOUBLE, partner, k,
                         &phi[k][0][1],   imax-2, MPI_DOUBLE, partner, k,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            int kk = k - 1;
            for (int j = 1; j < j_m; j++)
                for (int i = 1; i < imax-1; i++)
                    phi[kk][j][i] = (
                        phi[kk-1][j][i] + phi[kk][j-1][i] +
                        phi[kk][j][i-1] + phi[kk][j][i+1] +
                        phi[kk][j+1][i] + phi[kk+1][j][i]
                    ) / 6.0;
        }
    }

    if (my_rank == 1) {
        int k = kmax - 2;
        for (int j = 1; j < j_m; j++)
            for (int i = 1; i < imax-1; i++)
                phi[k][j][i] = (
                    phi[k-1][j][i] + phi[k][j-1][i] +
                    phi[k][j][i-1] + phi[k][j][i+1] +
                    phi[k][j+1][i] + phi[k+1][j][i]
                ) / 6.0;
    }
}


int main(int argc, char **argv) {
    int my_rank, nprocs;
    int num_iters, kmax, jmax, imax;
    double ***phi;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        // let rank 0 handle the input argumentss
        num_iters = atoi(argv[1]);
        kmax      = atoi(argv[2]);
        jmax      = atoi(argv[3]);
        imax      = atoi(argv[4]);
    }
    //then gpthelped me find a way to send them using broadcasting instead of just sending and recieving
    MPI_Bcast(&num_iters, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&kmax,       1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&jmax,       1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&imax,       1, MPI_INT, 0, MPI_COMM_WORLD);

    /*alllocate local slab: kmax × (jmax/2+1) × imax */
    int local_j = jmax/2 + 1;
    allocate_array3D(kmax, local_j, imax, &phi);

    /*initialize local points */
    initialize_array(kmax, local_j, imax, phi);

    /*run iterations */
    for (int n = 0; n < num_iters; n++)
      GS_iteration_2_chunks_mpi(my_rank, kmax, jmax, imax, phi);

    free_array3D(kmax, local_j, phi);
    MPI_Finalize();
    return 0;
}
