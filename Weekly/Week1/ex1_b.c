#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int n;
    printf("Choose size n of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Values generated: ");
    for (int i = 0; i < n; i++){
        arr[i] = rand() % (101);
        printf("%d, ", arr[i]);
    }

    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < n; i++){
        if (arr[i] > max){
            max = arr[i];
        }
        if (arr[i] < min){
            min = arr[i];
        }
    }

    printf("\nMax value: %d\n", max);
    printf("Min value: %d\n", min);
    

    return 0;
}