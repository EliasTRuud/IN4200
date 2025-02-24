// Write program to verify limit of 1 - 1/2**2 + 2/2**4 + ... is 4/5

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    double result = 0.0;

    /*

    */

    for (int i = 0; i<10; i++)
        result += pow(-1, i) / pow(2, 2 * i);̇

    printf("Result: %f\n", result);
    printf("Target: %f\n", 4. / 5.);
    printf("Close enough?: %s\n", (result - 4./5. < 1e-12) ? "Yes it is close enough" : "No");
}̇