// Lec09_BinHeap.cpp
// 실습: Binary Min-Heap 구현
// 교수님 코드 기반 (슬라이드 p.35~38)

#include <stdio.h>

const int MAX_HEAP = 200;

class BinHeap {
    int heap[MAX_HEAP];   // index 0 사용 안 함 (1부터 시작)
public:
    int currentSize;

    BinHeap() { currentSize = 0; heap[0] = 0; }

    bool isEmpty() { return currentSize == 0; }

    // perc_up (p.36)
    void percUp(int i) {
        while (i / 2 > 0) {
            if (heap[i] < heap[i / 2]) {
                int tmp     = heap[i / 2];
                heap[i / 2] = heap[i];
                heap[i]     = tmp;
            }
            i = i / 2;
        }
    }

    // insert (p.36)
    void insert(int k) {
        heap[++currentSize] = k;
        percUp(currentSize);
    }

    // min_child (p.37)
    int minChild(int i) {
        if (i * 2 + 1 > currentSize) return i * 2;
        return (heap[i * 2] < heap[i * 2 + 1]) ? i * 2 : i * 2 + 1;
    }

    // perc_down (p.37)
    void percDown(int i) {
        while (i * 2 <= currentSize) {
            int mc = minChild(i);
            if (heap[i] > heap[mc]) {
                int tmp  = heap[i];
                heap[i]  = heap[mc];
                heap[mc] = tmp;
            }
            i = mc;
        }
    }

    // del_min: 최솟값 삭제 후 반환 (p.38)
    int delMin() {
        int retVal      = heap[1];
        heap[1]         = heap[currentSize];
        currentSize     = currentSize - 1;
        percDown(1);
        return retVal;
    }

    void display() {
        printf("Heap [size=%d]:", currentSize);
        for (int i = 1; i <= currentSize; i++) printf(" %d", heap[i]);
        printf("\n");
    }
};

int main() {
    BinHeap h;

    h.insert(5);  h.insert(9);  h.insert(11);
    h.insert(14); h.insert(18); h.insert(19);
    h.insert(21); h.insert(33); h.insert(17);
    h.display();

    printf("delMin => %d\n", h.delMin()); h.display();
    printf("delMin => %d\n", h.delMin()); h.display();
    printf("delMin => %d\n", h.delMin()); h.display();

    return 0;
}
