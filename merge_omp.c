#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 256

int data[MAX_SIZE];
int temp[MAX_SIZE];
int num_threads = 4; // Change this to adjust the number of threads

typedef struct {
    int start;
    int end;
} Params;

void merge(int start, int mid, int end) {
    int i = start, j = mid + 1, k = start;

    while (i <= mid && j <= end) {
        if (data[i] <= data[j]) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = data[i++];
    }

    while (j <= end) {
        temp[k++] = data[j++];
    }

    for (i = start; i <= end; i++) {
        data[i] = temp[i];
    }
}

void* merge_sort(void* arg) {
    Params* params = (Params*)arg;
    int start = params->start;
    int end = params->end;

    if (start < end) {
        int mid = (start + end) / 2;

        Params left_params = {start, mid};
        Params right_params = {mid + 1, end};

        pthread_t left_thread, right_thread;
        pthread_create(&left_thread, NULL, merge_sort, &left_params);
        pthread_create(&right_thread, NULL, merge_sort, &right_params);

        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);

        merge(start, mid, end);
    }

    pthread_exit(NULL);
}

int main() {
    for (int i = 0; i < MAX_SIZE; i++) {
        data[i] = rand() % 256; // Populate array with random numbers from 0 to 255
    }

    pthread_t sort_threads[num_threads];
    Params params[num_threads];

    int chunk_size = MAX_SIZE / num_threads;
    for (int i = 0; i < num_threads; i++) {
        params[i].start = i * chunk_size;
        params[i].end = (i + 1) * chunk_size - 1;
        pthread_create(&sort_threads[i], NULL, merge_sort, &params[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(sort_threads[i], NULL);
    }

    merge(0, chunk_size - 1, MAX_SIZE - 1);

    printf("Sorted array:\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}
