// Lec09_PriorityQueue.cpp
// 실습: Priority Queue - BinHeap을 이용한 우선순위 큐
// 교수님 코드 기반 (슬라이드 p.41~42)
// - enqueue() : queue에 새 요소 삽입
// - dequeue() : 최대 우선순위 요소 삭제 및 반환
// - peek()    : 최대 우선순위 요소 반환 (삭제 X)

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
        if (i*2+1 > currentSize) return i*2;
        return (heap[i*2] < heap[i*2+1]) ? i*2 : i*2+1;
    }
    void percDown(int i) {
        while (i*2 <= currentSize) {
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

// 높은 값이 높은 우선순위 (Max-PQ)
// MinHeap에 부호 반전해서 삽입 → 가장 큰 값이 먼저 나옴
class PriorityQueue {
    BinHeap heap;
public:
    void enqueue(int item) { heap.insert(-item); }   // 부호 반전
    int  dequeue()         { return -heap.delMin(); }
    int  peek() {
        int val = heap.delMin();
        heap.insert(val);
        return -val;
    }
    bool isEmpty()         { return heap.isEmpty(); }
};

int main() {
    // p.41 예시: 4 → 8 → 2 순서로 입력, 우선순위 큐 = 8 → 4 → 2
    PriorityQueue pq;

    pq.enqueue(4);
    pq.enqueue(8);
    pq.enqueue(2);

    printf("peek => %d\n",     pq.peek());      // 8 (삭제 X)
    printf("dequeue => %d\n",  pq.dequeue());   // 8
    printf("dequeue => %d\n",  pq.dequeue());   // 4
    printf("dequeue => %d\n",  pq.dequeue());   // 2

    return 0;
}
