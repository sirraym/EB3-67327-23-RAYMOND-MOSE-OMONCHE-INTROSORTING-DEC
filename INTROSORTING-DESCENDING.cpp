#include <iostream>
#include <cmath>
using namespace std;

int comparisons = 0;
int swaps = 0;

// Swap function
void swapValues(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    swaps++;
}

// Insertion Sort (Descending)
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] < key) { // CHANGED
            comparisons++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Partition (Descending)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] > pivot) { // CHANGED
            i++;
            swapValues(arr[i], arr[j]);
        }
    }
    swapValues(arr[i + 1], arr[high]);
    return i + 1;
}

// Heapify (Max Heap for Descending)
void heapify(int arr[], int n, int i, int offset) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        comparisons++;
        if (arr[offset + left] > arr[offset + largest])
            largest = left;
    }

    if (right < n) {
        comparisons++;
        if (arr[offset + right] > arr[offset + largest])
            largest = right;
    }

    if (largest != i) {
        swapValues(arr[offset + i], arr[offset + largest]);
        heapify(arr, n, largest, offset);
    }
}

// Heap Sort (Descending)
void heapSort(int arr[], int begin, int end) {
    int n = end - begin + 1;

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, begin);

    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        swapValues(arr[begin], arr[begin + i]);
        heapify(arr, i, 0, begin);
    }
}

// Introsort Utility
void introSortUtil(int arr[], int begin, int end, int depthLimit) {
    int size = end - begin + 1;

    if (size < 16) {
        insertionSort(arr, begin, end);
        return;
    }

    if (depthLimit == 0) {
        heapSort(arr, begin, end);
        return;
    }

    int pivot = partition(arr, begin, end);

    introSortUtil(arr, begin, pivot - 1, depthLimit - 1);
    introSortUtil(arr, pivot + 1, end, depthLimit - 1);
}

// Main Introsort
void introSort(int arr[], int n) {
    int depthLimit = 2 * log(n);
    introSortUtil(arr, 0, n - 1, depthLimit);
}

// Print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Main function
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    introSort(arr, n);

    cout << "Sorted Array (Descending): ";
    printArray(arr, n);

    cout << "Comparisons: " << comparisons << endl;
    cout << "Swaps: " << swaps << endl;

    return 0;
}