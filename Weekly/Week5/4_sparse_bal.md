Ex 4:

Let us look at the sparse matrix-vector multiplication C = C + A ∗ B, where
the sparse matrix A is stored in the compressed row storage (CRS) format.
That is, three arrays are used to store the nonzero values of A and remember
where these nonzeros are located in the matrix:

• 1D array val, of length Nnz, stores all the nonzero values of the sparse
matrix;
• 1D array col idx , of length Nnz, records the original column positions
of all the nonzero values;
• 1D array row ptr, of length N + 1, contains the indices at which new
rows start in array val. (N is the number of rows and columns in
matrix A.)

The implementation of a sparse matrix-vector multiplication, using the
CRS format for storing A, can thus be as follows:

for (i=0; i<N; i++) {
    tmp = C[i];
    for (j=row_ptr[i]; j<row_ptr[i+1]; j++)
        tmp = tmp + val[j]*B[col_idx[j]];
    C[i] = tmp;
}


It was shown in the slides for the third lecture of Chapter 3 that the
“best-case” code balance for the above code segment is:
N_nz = number all non zero elements in matrix, usually larger than N. (N < N_nz << N**2)
N = number of cols and rows


( N_nz(1 + 0.5) + 0.5*N      + N   +  2N ) /  (2*N_nz) = 3/4 + 7/4 * N/N_nz

( val + idx)    + row_ptr[i] + B[] +  C(load and stored N times)
divided by 2*N_nz = FLOPS


What is the “worst-case” code balance?
- Only things that can change is B vector. If there is not enough space in the cache for B
it would need to be reloaded every time. In the worst case it would be N_nz times.
B -> cache_line/Word_size * N_nz
E.g 32 bytes/ 8 bytes (double) = 4


