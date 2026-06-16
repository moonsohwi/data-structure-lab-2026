// Lec09_HeapSort.cpp
// 실습: Heap Sort - BinHeap을 이용한 정렬
// 교수님 코드 기반 (슬라이드 p.40)

#include <stdio.h>

const int MAX_HEAP = 200;

class BinHeap {
    int heap[MAX_HEAP];
public:
    int currentSize;
    BinHeap() { currentSize = 0; heap[0] = 0; }
    bool isEmpty() { return currentSize == 0; }

    void percUp(int i) {
        while (i / 2 > 0) {
            if (heap[i] < heap[i / 2]) {
                int tmp = heap[i/2]; heap[i/2] = heap[i]; heap[i] = tmp;
            }
            i = i / 2;
        }
    }
    void insert(int k) { heap[++currentSize] = k; percUp(currentSize); }

    int minChild(int i) {
        if (i * 2 + 1 > currentSize) return i * 2;
        return (heap[i*2] < heap[i*2+1]) ? i*2 : i*2+1;
    }
    void percDown(int i) {
        while (i * 2 <= currentSize) {
            int mc = minChild(i);
            if (heap[i] > heap[mc]) {
                int tmp = heap[i]; heap[i] = heap[mc]; heap[mc] = tmp;
            }
            i = mc;
        }
    }
    int delMin() {
        int retVal  = heap[1];
        heap[1]     = heap[currentSize--];
        percDown(1);
        return retVal;
    }
};

// 교수님 코드 (p.40)
void heapsort(int arr[], int n, int result[]) {
    BinHeap heap;
    for (int i = 0; i < n; i++)
        heap.insert(arr[i]);
    for (int i = 0; i < n; i++)
        result[i] = heap.delMin();
    // result 배열 reverse() 하면 내림차순
}

int main() {
    int arr[]  = { 54, 26, 93, 17, 77, 31, 44, 55, 20 };
    int n      = sizeof(arr) / sizeof(arr[0]);
    int sorted[100];

    printf("정렬 전: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    heapsort(arr, n, sorted);

    printf("정렬 후: ");
    for (int i = 0; i < n; i++) printf("%d ", sorted[i]);
    printf("\n");

    return 0;
}
