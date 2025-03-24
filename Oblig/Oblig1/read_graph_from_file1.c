#include <stdio.h>
#include <stdlib.h>

void read_graph_from_file1(char *filename){
    FILE *fp = fopen(filename,"r");
    if (fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }

    char line1[1024];
    char title1[1024];
    int nodes;
    int edges;

    //use fscan https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/ as reccomended for
    // structured data files, use fgets for reading full text lines

    //skip first line
    fgets(line1, sizeof(line1), fp);

    //read title
    fgets(title1, sizeof(title1), fp);

    // read nodes and edges, gpt helped. As long as ssame format we can look for exact strings
    if (sscanf(line, "# Nodes: %d Edges: %d", &nodes, &edges) == 2) {
        printf("Nodes: %d, Edges: %d\n", nodes, edges);
    } else {
        printf("Parsing failed.\n");
    }

    


}

int main()
{
    /* code */
    return 0;
}
