#include <stdio.h>
#include <omp.h>
#include<stdlib.h>
#define ARRAY_SIZE 256

void selection_sort(int arr[], int size) {
    int i, j, min_index, temp;
    #pragma omp parallel for private(i, j, min_index, temp)
    for (i = 0; i < size - 1; i++) {
        min_index = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
        }
    }
}

int main() {
    int arr[ARRAY_SIZE];

    // Initialize array with random numbers from 0 to 255
    #pragma omp parallel for
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 256; // Generate random numbers from 0 to 255
    }

    printf("Original array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    selection_sort(arr, ARRAY_SIZE);

    printf("\nSorted array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
