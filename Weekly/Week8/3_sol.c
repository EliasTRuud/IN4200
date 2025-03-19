#include <stdio.h>
#include <stdbool.h> // For using bool type

// Function to swap two elements
void swap(float *x, float *y) {
    float temp = *x;
    *x = *y;
    *y = temp;
}

// Improved Odd-Even Transposition Sort
void odd_even_sort(int n, float *a) {
    bool sorted; // Flag to track if swaps occur

    for (int i = 1; i <= n; i++) {  // n passes at most
        sorted = true;  // Assume sorted, will be set false if swap occurs

        if (i % 2 == 1) {  // Odd phase
            for (int j = 0; j < n - 1; j+=2 ) {
                if (a[j] > a[j + 1]) {
                    swap(&a[j], &a[j + 1]);
                    sorted = false;
                }
            }
        } else {  // Even phase
            for (int j = 1; j < n - 1; j+= 2) {
                if (a[j] > a[j+1]) {
                    swap(&a[j], &a[j+1]);
                    sorted = false;
                }
            }
            // If n is odd, check the last pair separately
            if (n % 2 == 0 && a[n - 2] > a[n - 1]) {
                swap(&a[n - 2], &a[n - 1]);
                sorted = false;
            }
        }

        // If no swaps occurred in a full pass, list is sorted
        if (sorted) break;
    }
}


// Pragma omp, shared
// or we can remove flag and just use normal pragma omp for
void omp_odd_even_sort(int n, float *arr) {
    for (int i = 0; i < n; i++) {  // n iterations
        bool swapped = false;

        // Parallel Odd phase (i is even) - Compare and swap pairs: (0,1), (2,3), ...
        #pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // Parallel Even phase (i is odd) - Compare and swap pairs: (1,2), (3,4), ...
        #pragma omp parallel for shared(arr, swapped)
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // Early termination if no swaps happened
        if (!swapped) break;
    }
}


// Function to print an array
void print_array(int n, float *a) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", a[i]);
    }
    printf("\n");
}

// Main function to test the sorting algorithm
int main() {
    float arr[] = {5.2, 3.1, 8.4, 2.7, 1.9, 4.6, 7.5}; // Odd-length list
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    print_array(n, arr);

    odd_even_sort(n, arr);

    printf("Sorted array:\n");
    print_array(n, arr);

    return 0;
}
