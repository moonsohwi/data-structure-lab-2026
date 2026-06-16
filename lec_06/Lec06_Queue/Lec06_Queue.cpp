// Lec06_Queue.cpp
// 실습: Queue 클래스 - FIFO (선입선출) 구현 및 동작 확인
// 교수님 코드 기반 (슬라이드 p.8, p.15)

#include <stdio.h>
#include <stdlib.h>

const int MAX_QUEUE_SIZE = 20;

class Queue {
    int  data[MAX_QUEUE_SIZE];
    int  front, rear, count;
public:
    Queue() { front = 0; rear = 0; count = 0; }

    bool isEmpty() { return count == 0; }
    bool isFull()  { return count == MAX_QUEUE_SIZE; }
    int  size()    { return count; }

    // 후단(rear)에 삽입
    void enqueue(int item) {
        if (isFull()) { printf("Queue Full\n"); return; }
        data[rear] = item;
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        count++;
    }

    // 전단(front)에서 삭제 후 반환
    int dequeue() {
        if (isEmpty()) { printf("Queue Empty\n"); return -1; }
        int item = data[front];
        front = (front + 1) % MAX_QUEUE_SIZE;
        count--;
        return item;
    }

    void display() {
        printf("[Queue 항목 수 = %d] ==>", count);
        int idx = front;
        for (int i = 0; i < count; i++) {
            printf(" %d", data[idx]);
            idx = (idx + 1) % MAX_QUEUE_SIZE;
        }
        printf("\n");
    }
};

int main() {
    Queue q;

    // FIFO 동작 확인 (슬라이드 p.15)
    q.enqueue(10); q.display();
    q.enqueue(20); q.display();
    q.enqueue(30); q.display();

    printf("dequeue => %d\n", q.dequeue()); q.display();
    printf("dequeue => %d\n", q.dequeue()); q.display();
    printf("dequeue => %d\n", q.dequeue()); q.display();

    return 0;
}
