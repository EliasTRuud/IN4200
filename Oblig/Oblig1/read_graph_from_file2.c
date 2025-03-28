#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"


void read graph from file2 (char *filename, int *N, int **row ptr, int **col idx, double **val){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file\n");
        exit(1);
    }

    
}