#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

double** createMatrix2D(int N) {
    double **matrix = malloc(N * sizeof(double *));
    if (matrix == NULL) {
        perror("malloc failed");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        matrix[i] = malloc(N * sizeof(double));
        if (matrix[i] == NULL) {
            perror("malloc failed");
            exit(1);
        }
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 0.0;
        }
    }
    return matrix;
}

void printMatrix2D(double **matrix, int n) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix2D(double **matrix, int n) {
    for (int i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
}


int read_graph_from_file1(char *filename, int *N, double ***linkmatrix) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file\n");
        exit(1);
    }

    char line1[200];
    char title1[100];
    char line3[100];
    char line4[100];
    int nodes, edges;

    // Skip first line
    fgets(line1, sizeof(line1), fp);

    // Read title
    fgets(title1, sizeof(title1), fp);

    // Read line 3 and extract nodes and edges.
    fgets(line3, sizeof(line3), fp);
    printf("Read line: %s", line3);
    if (sscanf(line3, "# Nodes: %d Edges: %d", &nodes, &edges) != 2) {
        printf("Parsing failed.\n");
        fclose(fp);
        exit(1);
    }
    printf("Nodes: %d, Edges: %d\n", nodes, edges);

    // Skip line 4
    fgets(line4, sizeof(line4), fp);

    int *edgeArr = malloc(sizeof(int) * nodes);
    for (int i = 0; i < nodes; i++) {
        edgeArr[i] = 0;
    }

    // Read the rest of the file, filling the matrix.
    // length is edges and format is: int int
    // add +1 to index [int][int] in linkmatrix array

    /*
    Inbound links is added to the matrix, ignore self links.
    Store in matrix and edge array which i keep track of total inbound links per column
    0 1 --> matrix[0][1]

    so i wanna add to position matrix[i][j] and edgeArr[j]
    */
    for (int i = 0; i < edges; i++) {
        int u, v;
        fscanf(fp, "%d %d", &u, &v);
        //printf("Edge: %d %d\n", u, v);

         // index is out of range, then skip
        if (u < 0 || u >= nodes || v < 0 || v >= nodes) {
            continue;
        }
        if (u == v) {
            // skip self links
            continue;
        }
        (*linkmatrix)[v][u] += 1;
        edgeArr[u]++;
    }
    fclose(fp); //close file
    
    // Divide by total amount of inbound links by column
    for (int j = 0; j < nodes; j++) {
        if (edgeArr[j] != 0) {  //division by zero.
            for (int i = 0; i < nodes; i++) {
                (*linkmatrix)[i][j] /= edgeArr[j];
            }
        }
    }

    free(edgeArr);
    return 0;
}
