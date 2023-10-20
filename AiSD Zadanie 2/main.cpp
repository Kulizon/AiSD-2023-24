#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

template <typename T> void swap(T* toSort, int i, int j) {
    T temp = toSort[i];
    toSort[i] = toSort[j];
    toSort[j] = temp;
}

template <typename T> void bubbleSort(T* toSort, int start, int end) {
    for (int i = start; i < end; i++)
    {
        for (int i = start; i < end; i++)
        {
            if (toSort[i + 1] < toSort[i]) {
                swap(toSort, i, i+1);
            }
        }
    }
}

template <typename T> int partition(T* toSort, int start, int end) {
    T p = toSort[end]; // pivot
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (toSort[j] <= p) {
            i++;
            
            swap(toSort, i, j);
        }
    }

    swap(toSort, i+1, end);
  
    return (i + 1);
 
}

template <typename T> void quickSort(T* toSort, int start, int end) {
    if (start >= end) {
        return;
    }

    // pivot
    int p = partition(toSort, start, end);

    quickSort(toSort, start, p-1);
    quickSort(toSort, p+1, end);
}

template <typename T> bool areSame(T a, T b) {
    return a - b < 0.000001;
}

template <typename T> bool isSortedCorrectly(T* arr, int size, void (*sortFunction)(T*, int, int)) {
    T copy1[size];
    T copy2[size];

    std::copy (arr, arr+size, copy1);  
    std::copy (arr, arr+size, copy2);  

    sortFunction(copy1, 0, size-1);
    std::sort(copy2, copy2 + size);

    if (size > 0) {
        std::cout << "Original array: [";
        for (int i = 0; i < size - 1; i++) {
            std::cout << arr[i] << ", ";
        };
        std::cout << arr[size - 1] << "]" << std::endl;

        std::cout << "Sorted array: [";
        for (int i = 0; i < size - 1; i++) std::cout << copy1[i] << ", ";
        std::cout << copy1[size - 1] << "]" << std::endl << std::endl;
    } else {
        std::cout << "Original array: []" << std::endl;
        std::cout << "Sorted array: []" << std::endl << std::endl;
    }


    for (int i = 0; i < size; i++) {
        if (!areSame(copy1[i], copy2[i])) {
            return false;
        }
    }

    return true;
}

int main() {
    int intArray1[] = {42, 17, 89, 5, 33, 61, 10, 77};
    int intArray2[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    int intArray3[] = {8, 64, 21, 37};

    float floatArray1[] = {3.14f, 6.2f, 1.8f, 9.7f, 2.3f, 5.9f, 8.6f, 4.5f};
    float floatArray2[] = {7.2f, 5.1f, 2.7f, 9.4f, 1.3f, 6.8f, 3.9f, 8.5f};
    float floatArray3[] = {4.4f};

    double doubleArray1[] = {0.601, 0.555, 0.555, 0.555, 0.333};
    double doubleArray2[] = {};
    double doubleArray3[] = {0.923, 0.789};


    std::cout << "=========== BubbleSort ===========" << std::endl;
    assert(isSortedCorrectly(intArray1, sizeof(intArray1) / sizeof(intArray1[1]), bubbleSort));
    assert(isSortedCorrectly(intArray2, sizeof(intArray2) / sizeof(intArray2[1]), bubbleSort));
    assert(isSortedCorrectly(intArray3, sizeof(intArray3) / sizeof(intArray3[1]), bubbleSort));
    
    assert(isSortedCorrectly(floatArray1, sizeof(floatArray1) / sizeof(floatArray1[1]), bubbleSort));
    assert(isSortedCorrectly(floatArray2, sizeof(floatArray2) / sizeof(floatArray2[1]), bubbleSort));
    assert(isSortedCorrectly(floatArray3, sizeof(floatArray3) / sizeof(floatArray3[1]), bubbleSort));

    assert(isSortedCorrectly(doubleArray1, sizeof(doubleArray1) / sizeof(doubleArray1[1]), bubbleSort));
    assert(isSortedCorrectly(doubleArray2, sizeof(doubleArray2) / sizeof(doubleArray2[1]), bubbleSort));
    assert(isSortedCorrectly(doubleArray3, sizeof(doubleArray3) / sizeof(doubleArray3[1]), bubbleSort));

    std::cout << "=========== QuickSort ===========" << std::endl; 
    assert(isSortedCorrectly(intArray1, sizeof(intArray1) / sizeof(intArray1[1]), quickSort));
    assert(isSortedCorrectly(intArray2, sizeof(intArray2) / sizeof(intArray2[1]), quickSort));
    assert(isSortedCorrectly(intArray3, sizeof(intArray3) / sizeof(intArray3[1]), quickSort));
    
    assert(isSortedCorrectly(floatArray1, sizeof(floatArray1) / sizeof(floatArray1[1]), quickSort));
    assert(isSortedCorrectly(floatArray2, sizeof(floatArray2) / sizeof(floatArray2[1]), quickSort));
    assert(isSortedCorrectly(floatArray3, sizeof(floatArray3) / sizeof(floatArray3[1]),quickSort));

    assert(isSortedCorrectly(doubleArray1, sizeof(doubleArray1) / sizeof(doubleArray1[1]), quickSort));
    assert(isSortedCorrectly(doubleArray2, sizeof(doubleArray2) / sizeof(doubleArray2[1]), quickSort));
    assert(isSortedCorrectly(doubleArray3, sizeof(doubleArray3) / sizeof(doubleArray3[1]), quickSort));
}   