# Comparative-Analysis-of-Sorting-Algorithms-using-Pthreads-and-OpenMP
1. Introduction: Sorting algorithms are fundamental operations in computer science, essential for organizing data efficiently. This project aims to compare the performance of five sorting algorithms—Bubble Sort, Radix Sort, Selection Sort, Merge Sort, and Quick Sort—implemented using two parallel programming paradigms, Pthreads and OpenMP.
2. Objectives:
Implement sorting algorithms using Pthreads and OpenMP to leverage parallelism.
Analyze and compare the performance of each algorithm under varying dataset sizes.
Evaluate the scalability and efficiency of Pthreads and OpenMP implementations.
3. Sorting Algorithms:
Bubble Sort: A simple comparison-based algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.
Radix Sort: Radix Sort is a non-comparative sorting algorithm that sorts integers by grouping digits from the least significant digit (LSD) to the most significant digit (MSD) or vice versa. It operates on the principle of distributing elements into buckets based on each digit's value and then collecting them back in order.
Selection Sort: Repeatedly finds the minimum element from the unsorted part and moves it to the beginning.
Merge Sort: Divides the array into two halves, sorts each half recursively, and then merges them back together.
Quick Sort: Chooses a 'pivot' element from the array and partitions the other elements into two sub-arrays according to whether they are less than or greater than the pivot.
4. Implementation:
Pthreads: Utilized for explicit thread-level parallelism. Each sorting algorithm is parallelized by dividing the dataset among multiple threads.
OpenMP: Employed for directive-based parallelism. Parallel regions are defined using compiler directives, and the sorting algorithms are adapted to exploit these parallel constructs.
5. Methodology:
Dataset: 0-255
Performance Metrics: Recorded execution time
Experimental Setup: Ran experiments on a machine with multi-core processor architecture to observe the impact of parallelism.


