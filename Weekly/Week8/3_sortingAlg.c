#include <stdio.h>
#include <stdbool.h> // For using bool type

void swap(float *x, float *y){
    float temp = *x;
    *x = *y;
    *y = temp;
}

void print_array(int n, float *a) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", a[i]);
    }
    printf("\n");
}

void sort{int n, float *arr}{
    bool allSorted;

    for (int i = 1; i<=n; i++){
        allSorted = true; //assume sorted then change to false if we find its not
    }
}




