#include <stdio.h>

// Function to merge two sorted subarrays into a single sorted array
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    // Calculate sizes of two subarrays to be merged
    int n1 = m - l + 1;  // Size of left subarray
    int n2 = r - m;      // Size of right subarray

    // Create temporary arrays to store the subarrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];     // Copy elements to left subarray
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j]; // Copy elements to right subarray

    // Initialize indices for merging
    i = 0;  // Initial index of left subarray
    j = 0;  // Initial index of right subarray
    k = l;  // Initial index of merged array

    // Merge the temporary arrays back into arr[l..r]
    while (i < n1 && j < n2) {
        // Compare elements from both subarrays and place the smaller one
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
