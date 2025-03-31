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
        arr[i] = 0.0;
    }
    return arr;
}

void read_graph_from_file2(char *filename, int *N, int **row_ptr, int **col_idx, double **val){
    /*
    Reads webgraph into CRS format:
        - 3 arrays, values[N], col[N], row_ptr[n<<N]
        - 
    */
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

    //same code as last version
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


    //Read into CRS
    int validLinks = 0;
    int *inbounds[] = createArray_int(N); //containing inbound nodes
    int *outbounds[] = createArray_int(N);
    

    // First pass count valid links
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
        // updates the number of inbound and outbound links for each node.
        inbounds[v]++;     
        outbounds[u]++;
        validLinks += 1;
    }
    //test print
    printf("validLinks: %d\n", validLinks);

    // row_ptr: length = nodes + 1, col_idx and val: length = validLinks
    // Allocate CRS arrays.
    *row_ptr = createArray_int(nodes + 1);   // row_ptr length = nodes+1
    *col_idx = createArray_int(validLinks);    // col_idx length = validLinks
    *val = createArray(validLinks);            // val length = validLinks

    // Build row_ptr: row_ptr[0] = 0, row_ptr[i+1] = row_ptr[i] + inbounds[i]
    (*row_ptr)[0] = 0;
    for (int i = 0; i < nodes; i++) {
        (*row_ptr)[i + 1] = (*row_ptr)[i] + inbounds[i];
    }

    // Allocate temporary array to track fill per row.
    int *current_count = calloc(nodes, sizeof(int));
    if (current_count == NULL) {
        printf("Memory allocation failed for current_count\n");
        fclose(fp);
        exit(1);
    }
    
    // Rewind the file to perform second pass.
    rewind(fp);
    // Skip header lines again.
    fgets(line1, sizeof(line1), fp);
    fgets(title1, sizeof(title1), fp);
    fgets(line3, sizeof(line3), fp);
    fgets(line4, sizeof(line4), fp);
    
    int pos;
    // Second pass: fill col_idx and val arrays.
    for (int i = 0; i < edges; i++) {
        if (fscanf(fp, "%d %d", &u, &v) != 2)
            continue;
        if (u < 0 || u >= nodes || v < 0 || v >= nodes)
            continue;
        if (u == v)
            continue;
        pos = (*row_ptr)[v] + current_count[v];
        (*col_idx)[pos] = u;
        if (outbounds[u] > 0)
            (*val)[pos] = 1.0 / outbounds[u];
        else
            (*val)[pos] = 0.0;
        current_count[v]++;
    }
    
    // Clean up temporary arrays.
    free(inbounds);
    free(outbounds);
    free(current_count);
    fclose(fp);
    
    // Function is declared as void, so don't return a value.
}