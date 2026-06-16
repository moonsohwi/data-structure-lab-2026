// Lec06_Deque.cpp
// 실습: Deque 클래스 - 전단/후단 모두에서 삽입·삭제 가능
// 교수님 코드 기반 (슬라이드 p.16~18)
// addFront / addRear / deleteFront / deleteRear / getFront / getRear

#include <stdio.h>
#include <stdlib.h>

const int MAX_DEQUE_SIZE = 20;

class Deque {
    int  data[MAX_DEQUE_SIZE];
    int  front, rear, count;
public:
    Deque() { front = MAX_DEQUE_SIZE - 1; rear = 0; count = 0; }

    bool isEmpty() { return count == 0; }
    bool isFull()  { return count == MAX_DEQUE_SIZE; }

    // 전단에 삽입 (p.16 addFront)
    void addFront(int e) {
        if (isFull()) { printf("Deque Full\n"); return; }
        data[front] = e;
        front = (front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
        count++;
    }

    // 후단에 삽입 (p.16 addRear = enqueue)
    void addRear(int e) {
        if (isFull()) { printf("Deque Full\n"); return; }
        data[rear] = e;
        rear = (rear + 1) % MAX_DEQUE_SIZE;
        count++;
    }

    // 전단 삭제 후 반환 (p.16 deleteFront = dequeue)
    int deleteFront() {
        if (isEmpty()) { printf("Deque Empty\n"); return -1; }
        front = (front + 1) % MAX_DEQUE_SIZE;
        count--;
        return data[front];
    }

    // 후단 삭제 후 반환 (p.16 deleteRear)
    int deleteRear() {
        if (isEmpty()) { printf("Deque Empty\n"); return -1; }
        rear = (rear - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
        count--;
        return data[rear];
    }

    int getFront() {
        if (isEmpty()) { printf("Deque Empty\n"); return -1; }
        return data[(front + 1) % MAX_DEQUE_SIZE];
    }
    int getRear() {
        if (isEmpty()) { printf("Deque Empty\n"); return -1; }
        return data[(rear - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE];
    }

    void display() {
        printf("[Deque 항목 수=%d] 전단=>", count);
        int idx = (front + 1) % MAX_DEQUE_SIZE;
        for (int i = 0; i < count; i++) {
            printf(" %d", data[idx]);
            idx = (idx + 1) % MAX_DEQUE_SIZE;
        }
        printf(" <=후단\n");
    }
};

int main() {
    // p.18 동작 확인: add_front(A), add_rear(B), add_front(C), add_rear(D)
    //                 delete_front() -> C, delete_rear() -> D
    Deque dq;

    dq.addFront(1);  dq.display();   // [1]
    dq.addRear(2);   dq.display();   // [1, 2]
    dq.addFront(3);  dq.display();   // [3, 1, 2]
    dq.addRear(4);   dq.display();   // [3, 1, 2, 4]

    printf("deleteFront => %d\n", dq.deleteFront()); dq.display(); // 3 제거
    printf("deleteRear  => %d\n", dq.deleteRear());  dq.display(); // 4 제거

    // Deque로 Stack 흉내 (addFront + deleteFront)
    printf("\n[Deque as Stack]\n");
    Deque stk;
    stk.addFront(10); stk.addFront(20); stk.addFront(30);
    stk.display();
    printf("pop => %d\n", stk.deleteFront());
    printf("pop => %d\n", stk.deleteFront());

    return 0;
}
