#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Function to merge two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));

    // Check for malloc failure
    if (L == NULL || R == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
        arr[k++] = L[i++];

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
        arr[k++] = R[j++];

    // Free temporary arrays
    free(L);
    free(R);
}

// Merge Sort function with OpenMP parallelization
void mergeSort(int arr[], int l, int r, int depth) {
    if (l < r) {
        // Same as (l + r) / 2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // If depth is greater than 0, parallelize
        if (depth > 0) {
            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    mergeSort(arr, l, m, depth - 1);
                }
                #pragma omp section
                {
                    mergeSort(arr, m + 1, r, depth - 1);
                }
            }
        }
        else {
            // Sequential execution
            mergeSort(arr, l, m, depth);
            mergeSort(arr, m + 1, r, depth);
        }

        merge(arr, l, m, r);
    }
}

// Utility function to print an array
void printArray(int A[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", A[i]);
        // Print a newline every 20 elements for better readability
        if ((i + 1) % 20 == 0)
            printf("\n");
    }
    // Ensure the array ends with a newline
    if (size % 20 != 0)
        printf("\n");
}

// Utility function to verify if the array is sorted
int isSorted(int A[], int size) {
    for (int i = 1; i < size; i++)
        if (A[i-1] > A[i])
            return 0;
    return 1;
}

int main() {
    // Define the size of the array
    const int arr_size = 1000;
    int *arr = (int*) malloc(arr_size * sizeof(int));

    // Check for malloc failure
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Populate the array with random integers between 0 and 9999
    for (int i = 0; i < arr_size; i++) {
        arr[i] = rand() % 10000;
    }

    printf("Generating an array of %d random integers...\n\n", arr_size);
    printf("Unsorted array:\n");
    printArray(arr, arr_size);
    printf("\n");

    // Set the number of threads
    int num_threads = 4;
    omp_set_num_threads(num_threads);

    // Determine the maximum depth for parallelism
    // For 4 threads, log2(4) = 2
    int max_depth = 2;

    // Start the timer
    double start_time = omp_get_wtime();

    // Start the merge sort within a parallel region
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergeSort(arr, 0, arr_size - 1, max_depth);
        }
    }

    // End the timer
    double end_time = omp_get_wtime();

    printf("Sorting completed.\n");
    printf("Time taken: %f seconds\n\n", end_time - start_time);

    printf("Sorted array:\n");
    printArray(arr, arr_size);
    printf("\n");

    // Verify if the array is sorted
    if (isSorted(arr, arr_size)) {
        printf("The array is sorted correctly.\n");
    }
    else {
        printf("The array is NOT sorted correctly.\n");
    }

    // Free the allocated memory
    free(arr);

    return 0;
}
