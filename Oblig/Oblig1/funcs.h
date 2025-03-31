#ifndef FUNCS_H
#define FUNCS_H

int read_graph_from_file1(char *filename, int *N, double ***linkmatrix);
void read_graph_from_file2 (char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations1(int N, double **hyperlink_matrix, double d, double epsilon, double *scores);
void PageRank_iterations2 (int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
void top_n_webpages (int N, double *scores, int n);

double** createMatrix2D(int N);
void printMatrix2D(double **matrix, int n);
void freeMatrix2D(double **matrix, int n);

double* createArray(int N);
int* createArray_int(int N);
void printArray(double *arr, int N);
void printArray_int(int *arr, int N);


#endif
