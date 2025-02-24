
Calculate code balance for the following loops, assuming that all arrays have
to be loaded from memory. (Arrays A, B and y contain double-precision
values.)

Code balance = data_traffic (load + store) / FLOPS

1 WORD = double precision
0.5 WORD = integer

a) Dense matrix-vector multiplication:
for (j=0; j<N; j++)
    for (i=0; i<N; i++)
        y[j] += A[j][i]*B[i];

traffic = 3 loads + 1 store
flops = 1 addition + 1 multiplication
code balance = 4/2 = 2 Words/FLOP 


b) Vector norm:
double s = 0.;
for (i=0; i<N; i++)
    s += A[i]*A[i];

coda balance = 1/2 words/FLOP

c) Scalar product:
double s = 0.;
for (i=0; i<N; i++)
    s += A[i]*B[i];

code balance = 2 loads / 2 flops = 1 words/FLOP


d)  Scalar product with indirect access:
double s = 0.;
for (i=0; i<N; i++)
    s += A[i]*B[K[i]];

traffic = 2 loads of double + 1 load of integer = 2 + 0.5 = 2.5 words
flops = 1 addition + 1 multiplication
code balance = 2.5 loads / 2 flops = 1.25 words/FLOP




