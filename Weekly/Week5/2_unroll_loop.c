// Unroll and unjam: 

/*
Exercise 2
Please apply “unroll and jam” (with 4 as the unroll depth) to the outer loop
of the following code:
for (j=0; j<N; j++)
    for (i=0; i<=j; i++)
        y[j] += A[j][i]*B[i];
Note: The value of N may not be divisible by 4.
*/



int main(){
    for (j=0; j<N; j++){
        for (i=0; i<=j; i++){
             y[j] += A[j][i]*B[i];           
        }
    }



    
    // Unroll and unjam
    for (j=0; j<N-(N % 4); j+=4) {// N - (N%4), there might be rest so we go up high as possibly as multiplier of 4
        for (i=0; i<=j; i++) {
            y[j] += A[j][i]*B[i];
            y[j+1] += A[j+1][i]*B[i];
            y[j+2] += A[j+2][i]*B[i];
            y[j+3] += A[j+3][i]*B[i];
        }
        // These values not included in the unrolled loop
        y[j+1] += A[j+1][j+1]*B[j+1];

        y[j+2] += A[j+2][j+1]*B[j+1];
        y[j+2] += A[j+2][j+2]*B[j+2];

        y[j+3] += A[j+3][j+1]*B[j+1];
        y[j+3] += A[j+3][j+2]*B[j+2];
        y[j+3] += A[j+3][j+3]*B[j+3];
    }

    // If N not divisble then fill in the slow way.
    for (int j = N - (N - (N%4)); j < N; j++){
        for (int i = 0; i <= j; i++){
            y[j] += A[j][i]*B[i];
        }
    }
           





    return 0;
}
