
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main{
    /*
    Write a C program that reads from a data file containing one day’s
    temperature measurements of the following format:   
    00:05 -0.1
    00:21 0.1
    00:29 -0.2
    ...

    Find out the highest and lowest temperatures and when they occurred.
    Compute also the average temperature and the associated standard deviation
    */

    // Two arrays, one time, one temp.
    // Loop over temperatures and find index of smallest and highest, also calculate the std deviation.

    // std dev: sqrt(1/N * sum(data - mean)**2), mean = sum / N
    FILE *fp = fopen("temperature.txt", "r");

    // Guard clause to check if file was opened successfully
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    // Get number of lines in file
    int N;
    fscanf(fp, "%d", &N);
    printf("N = %d\n", N);

    int n; // number of samples = numer of lines
    n = 0; 
    double *temps = malloc(n * sizeof(double));
    char **times = malloc(n * sizeof(char *)); // each string is an array of chars
    


    
    return 0;
}