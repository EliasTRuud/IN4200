#include <stdio.h>
#include <stdlib.h>

void read_graph_from_file1(char *filename, int *N, double ***linkmatrix){
    FILE *fp = fopen(filename,"r");
    if (fp == NULL){
        printf("Could not open file\n");
        return 1;
    }

    char line1[200];
    char title1[100];
    char line3[100];
    char line4[100];
    int nodes;
    int edges;

    //use fscan https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/ as reccomended for
    // structured data files, use fgets for reading full text lines

    //skip first line
    fgets(line1, sizeof(line1), fp);

    //read title
    fgets(title1, sizeof(title1), fp);

    //read line 3
    fgets(line3, sizeof(line3), fp);
    printf("Read line: %s\n", line3);
    // read nodes and edges, gpt help. As long as ssame format we can look for exact strings
    if (sscanf(line3, "# Nodes: %d Edges: %d", &nodes, &edges) == 2) {
        printf("Nodes: %d, Edges: %d\n", nodes, edges);
    } else {
        printf("Parsing failed.\n");
    }

    // skip line 4
    fgets(line4, sizeof(line4), fp)

    //Create hyperlink matrix of dim nodes x nodes. Fill with zeros
    double **linkMatrix = (double **)malloc(nodes * sizeof(double *));
    for (int i = 0; i < nodes; i++) {
        linkMatrix[i] = (double *)malloc(nodes * sizeof(double));
    }

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            linkMatrix[i][j] = 0.0;
        }
    }


    // Read in entries of matrix.


    

    // free up the 2d matrix
    for (i = 0; i < nodes; i++) {
        free(linkMatrix[i]);
    }
    free(linkMatrix);  
}

int main()
{
    /* code */
    char filename[] = "simple.txt";
    read_graph_from_file1(filename);
    return 0;
}
