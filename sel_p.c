#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 256
#define NUM_THREADS 4 // Number of threads to use

// Struct to pass arguments to the sorting function
struct ThreadArgs {
    int* arr;
    int size;
};

// Function to perform selection sort in a range
void* selection_sort_range(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    int* arr = args->arr;
    int size = args->size;

    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
        }
    }

    pthread_exit(NULL);
}

// Function to perform selection sort using multiple threads
void parallel_selection_sort(int arr[], int size) {
    pthread_t threads[NUM_THREADS];
    struct ThreadArgs args[NUM_THREADS];

    int chunk_size = size / NUM_THREADS;
    int remainder = size % NUM_THREADS;
    int offset = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].arr = arr + offset;
        args[i].size = chunk_size + (i < remainder ? 1 : 0);
        pthread_create(&threads[i], NULL, selection_sort_range, (void*)&args[i]);
        offset += args[i].size;
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    int arr[ARRAY_SIZE];

    // Initialize array with random numbers from 0 to 255
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 256; // Generate random numbers from 0 to 255
    }

    printf("Original array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    parallel_selection_sort(arr, ARRAY_SIZE);

    printf("\nSorted array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
