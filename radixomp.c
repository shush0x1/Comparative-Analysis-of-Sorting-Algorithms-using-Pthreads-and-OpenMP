#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to get the maximum value in arr[]
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

// Function to perform counting sort based on the digit represented by exp
void countSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    // Store count of occurrences of each digit in count[]
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        #pragma omp atomic
        count[digit]++;
    }

    // Change count[i] so that count[i] now contains actual
    // position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    #pragma omp parallel for
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        #pragma omp atomic
        count[digit]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to the current digit
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Radix Sort function using OpenMP
void radixSort(int arr[], int n) {
    // Find the maximum number to know the number of digits
    int max = getMax(arr, n);

    // Perform counting sort for every digit
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    const int SIZE = 10000;
    int arr[SIZE];

    // Generate random numbers between 0 and 10000
    srand(123); // Seed for reproducibility
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 10001;
    }

    printf("Original array:\n");
    printArray(arr, SIZE);

    // Perform Radix Sort using OpenMP
    double start_time = omp_get_wtime();
    radixSort(arr, SIZE);
    double end_time = omp_get_wtime();

    printf("Sorted array:\n");
    printArray(arr, SIZE);

    printf("Time taken: %.6f seconds\n", end_time - start_time);

    return 0;
}
