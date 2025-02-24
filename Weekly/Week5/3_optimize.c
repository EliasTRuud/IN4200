#include <math.h>


void foo (int N, double **mat, double **s, int *v) {
    int i,j;
    double val;

    for (j=0; j<N; j++)
        for (i=0; i<N; i++) {
            val = 1.0*(v[j]%256);
            mat[i][j] = s[i][j]*(sin(val)*sin(val)-cos(val)*cos(val));
        }
    }


void foo_optimzied(int N, double **mat, double **s, int *v) {
     // Val is not dependent on i, so move it inside j loop.
    // cos(2*theta)  = cos(theta)**2 - sin(theta)**2
    // Use lookup table of 255 entries which stores all the values of cos(2*val)

    int i,j;
    double val, trig;
    double cos_table[256];
    int vtab[N];

    for (i=0; i<=255; i++){
        cos_table[i] = -cos(2.0 * i);
    }


    // To avoid looking up the values in the inner loop we can quikcly map out the N indices.
    for (i=0; i< N; i++){
        vtab[i] = abs(v[i] % 256);
    }

    // Then finally calculate the matrix
    for (j=0; j<N; j++){
        for (i=0; i<N; i++) {
            mat[i][j] = s[i][j] * cos_table[ vtab[i] ];
        }
    }
    free cos_table;
    free vtab;
    }

int main(){
    return 0;
}