#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

double* createArray(int N) {
    double *arr = malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        arr[i] = 0.0;
    }
    return arr;
}

int* createArray_int(int N) {
    int *arr = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        arr[i] = 0;
    }
    return arr;
}

void printArray(double *arr, int N) {
    //Print the array of doubles
    for (int i = 0; i < N; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

void printArray_int(int *arr, int N){
    //Print the array of integers
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void read_graph_from_file2(char *filename, int *N, int **row_ptr, int **col_idx, double **val) {
    /*
    Reads webgraph into CRS format:
      - row_ptr: length = nodes + 1
      - col_idx and val: length = total valid links
    */
    FILE *fp = fopen(filename, "r");
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
    sscanf(line3, "# Nodes: %d Edges: %d", &nodes, &edges);
    printf("Nodes: %d, Edges: %d\n", nodes, edges);
    *N = nodes;

    // Skip line 4
    fgets(line4, sizeof(line4), fp);

    // First pass: count valid links and update inbound/outbound counts.
    int validLinks = 0;
    int *inbounds = createArray_int(nodes);  // inbound link count per node
    int *outbounds = createArray_int(nodes);   // outbound link count per node
    int u, v;
    for (int i = 0; i < edges; i++) {
        fscanf(fp, "%d %d", &u, &v);
        if (u < 0 || u >= nodes || v < 0 || v >= nodes)
            continue;
        if (u == v)
            continue;
        inbounds[v]++;
        outbounds[u]++;
        validLinks++;
    }
    printf("validLinks: %d\n", validLinks);

    // Allocate CRS arrays.
    *row_ptr = createArray_int(nodes + 1);   // row_ptr length = nodes+1
    *col_idx = createArray_int(validLinks);    // col_idx length = validLinks
    *val = createArray(validLinks);            // val length = validLinks



    // row_ptr: row_ptr[0] = 0, row_ptr[i+1] = row_ptr[i] + inbounds[i], helped by chatgpt this method with inbounds and outbounds
    (*row_ptr)[0] = 0;
    for (int i = 0; i < nodes; i++) {
        (*row_ptr)[i + 1] = (*row_ptr)[i] + inbounds[i];
    }

    // Allocate temporary array to track fill per row.
    int *current_count = calloc(nodes, sizeof(int));


    rewind(fp); //reset reader ponter
    // skip header lines again
    fgets(line1, sizeof(line1), fp);
    fgets(title1, sizeof(title1), fp);
    fgets(line3, sizeof(line3), fp);
    fgets(line4, sizeof(line4), fp);

    int pos;
    // Second pass, fills thhe col_idx and val arrays. helped by chatgpt
    for (int i = 0; i < edges; i++) {
        if (fscanf(fp, "%d %d", &u, &v) != 2)
            continue;
        if (u < 0 || u >= nodes || v < 0 || v >= nodes)
            continue;
        if (u == v)
            continue;
        pos = (*row_ptr)[v] + current_count[v];
        (*col_idx)[pos] = u;
        (*val)[pos] = (outbounds[u] > 0) ? (1.0 / outbounds[u]) : 0.0;
        current_count[v]++;
    }
    free(inbounds);
    free(outbounds);
    free(current_count);
    fclose(fp);
}
