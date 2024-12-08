#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_DIGITS 4
#define MAX_THREADS 4

// Structure to pass arguments to thread function
typedef struct {
    int* arr;
    int n;
    int exp;
} ThreadArgs;

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
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Change count[i] so that count[i] now contains actual
    // position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to the current digit
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Thread function to perform radix sort
void* radixSortThread(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    countSort(args->arr, args->n, args->exp);
    return NULL;
}

// Radix Sort function using pthread
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);

    // Create threads for each digit place (MAX_DIGITS times)
    pthread_t threads[MAX_THREADS];
    ThreadArgs args[MAX_THREADS];

    int exp = 1;
    for (int i = 0; i < MAX_DIGITS; i++) {
        exp *= 10;

        // Distribute work among threads
        int chunk_size = n / MAX_THREADS;
        for (int j = 0; j < MAX_THREADS; j++) {
            args[j].arr = &arr[j * chunk_size];
            args[j].n = (j == MAX_THREADS - 1) ? (n - j * chunk_size) : chunk_size;
            args[j].exp = exp;

            pthread_create(&threads[j], NULL, radixSortThread, (void*)&args[j]);
        }

        // Wait for all threads to complete
        for (int j = 0; j < MAX_THREADS; j++) {
            pthread_join(threads[j], NULL);
        }
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

    // Perform Radix Sort using pthread
    radixSort(arr, SIZE);

    printf("Sorted array:\n");
    printArray(arr, SIZE);

    return 0;
}
