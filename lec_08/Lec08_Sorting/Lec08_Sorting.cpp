// Lec08_Sorting.cpp
// 실습: Bubble / Selection / Insertion / Shell / Merge / Quick Sort

#include <stdio.h>

void printArr(int arr[], int n, const char* label) {
    printf("%s: ", label);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}
void copyArr(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = n - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
            }
}

// Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        int tmp = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = tmp;
    }
}

// Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Shell Sort
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int key = arr[i], j = i - gap;
            while (j >= 0 && arr[j] > key) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = key;
        }
}

// Merge
void merge(int arr[], int left, int mid, int right) {
    int tmp[100];
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right)
        tmp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= mid)   tmp[k++] = arr[i++];
    while (j <= right) tmp[k++] = arr[j++];
    for (int x = left; x <= right; x++) arr[x] = tmp[x];
}

// Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort - partition (교수님 코드 기반, 슬라이드 p.30)
int partition(int arr[], int first, int last) {
    int pivotValue = arr[first];
    int leftMark   = first + 1;
    int rightMark  = last;
    bool done      = false;

    while (!done) {
        while (leftMark <= rightMark && arr[leftMark] <= pivotValue)
            leftMark++;
        while (arr[rightMark] >= pivotValue && rightMark >= leftMark)
            rightMark--;

        if (rightMark < leftMark) {
            done = true;
        } else {
            int tmp = arr[leftMark];
            arr[leftMark]  = arr[rightMark];
            arr[rightMark] = tmp;
        }
    }
    int tmp = arr[first];
    arr[first]      = arr[rightMark];
    arr[rightMark]  = tmp;
    return rightMark;
}

void quickSort(int arr[], int first, int last) {
    if (first < last) {
        int splitPoint = partition(arr, first, last);
        quickSort(arr, first, splitPoint - 1);
        quickSort(arr, splitPoint + 1, last);
    }
}

int main() {
    int origin[] = { 54, 26, 93, 17, 77, 31, 44, 55, 20 };
    int n = sizeof(origin) / sizeof(origin[0]);
    int arr[100];

    printf("정렬 전: ");
    for (int i = 0; i < n; i++) printf("%d ", origin[i]);
    printf("\n\n");

    copyArr(origin, arr, n); bubbleSort(arr, n);     printArr(arr, n, "Bubble   ");
    copyArr(origin, arr, n); selectionSort(arr, n);  printArr(arr, n, "Selection");
    copyArr(origin, arr, n); insertionSort(arr, n);  printArr(arr, n, "Insertion");
    copyArr(origin, arr, n); shellSort(arr, n);      printArr(arr, n, "Shell    ");
    copyArr(origin, arr, n); mergeSort(arr, 0, n-1); printArr(arr, n, "Merge    ");
    copyArr(origin, arr, n); quickSort(arr, 0, n-1); printArr(arr, n, "Quick    ");

    return 0;
}
