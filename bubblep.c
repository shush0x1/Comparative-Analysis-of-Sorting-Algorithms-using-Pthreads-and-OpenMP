#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 256
#define NUM_THREADS 4

int arr[ARRAY_SIZE];

typedef struct {
    int start;
    int end;
} ThreadArgs;

void *bubbleSort(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    for (int i = args->start; i < args->end; i++) {
        for (int j = args->start; j < args->end - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];

    srand(time(NULL));

    // Initialize array with random numbers from 0 to 255
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 256;
    }

    int chunk_size = ARRAY_SIZE / NUM_THREADS;
    
    // Creating and running threads
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].start = i * chunk_size;
        args[i].end = (i + 1) * chunk_size;
        if (pthread_create(&threads[i], NULL, bubbleSort, (void *)&args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Joining threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merging chunks
    for (int i = 1; i < NUM_THREADS; i++) {
        for (int j = args[i].start; j < args[i].end; j++) {
            int key = arr[j];
            int k = j - 1;
            while (k >= 0 && arr[k] > key) {
                arr[k + 1] = arr[k];
                k--;
            }
            arr[k + 1] = key;
        }
    }

    // Printing sorted array
    printf("Sorted array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
