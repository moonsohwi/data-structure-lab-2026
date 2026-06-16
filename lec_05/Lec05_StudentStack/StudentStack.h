// StudentStack.h
// 슬라이드 p.25~26: ArrayStack (int) → Student로 교체
// 슬라이드 p.28~29: Student 클래스 + StudentStack(ArrayStack) 클래스

#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAX_STACK_SIZE = 20;
const int MAX_STRING     = 40;

// 오류 처리 함수 (슬라이드 p.26 우측 노란 박스)
inline void error(char* message) {
    printf("%s\n", message);
    exit(1);
}

// ──────────────────────────────────────────────
// Student 클래스 (슬라이드 p.28)
// ──────────────────────────────────────────────
class Student {
    int  id;                    // 학번
    char name[MAX_STRING];      // 이름
    char dept[MAX_STRING];      // 소속 학과
public:
    Student(int i = 0, const char* n = "", const char* d = "") {
        set(i, n, d);
    }
    void set(int i, const char* n, const char* d) {
        id = i;
        strcpy(name, n);        // 문자열 복사 함수
        strcpy(dept, d);        // 문자열 복사 함수
    }
    void display() {
        printf(" 학번:%-15d 성명:%-10s 학과:%-20s\n", id, name, dept);
    }
};

// ──────────────────────────────────────────────
// ArrayStack → StudentStack (슬라이드 p.25~26, p.29)
// p.29: int data[] → Student data[], 함수 시그니처 교체
// ──────────────────────────────────────────────
class StudentStack {
    int     top;                        // 요소의 개수
    Student data[MAX_STACK_SIZE];       // Student 배열 (p.29 핵심 변경)
public:
    StudentStack() { top = -1; }        // 스택 생성자
    ~StudentStack() {}                  // 스택 소멸자

    bool isEmpty() { return top == -1; }
    bool isFull()  { return top == MAX_STACK_SIZE - 1; }

    // 맨 위에 항목 삽입 (p.25)
    void push(Student e) {
        if (isFull()) error((char*)"스택 포화 에러");
        data[++top] = e;
    }

    // 맨 위 항목 삭제 후 반환 (p.26)
    Student pop() {
        if (isEmpty()) error((char*)"스택 공백 에러");
        return data[top--];
    }

    // 삭제하지 않고 요소 반환 (p.26)
    Student peek() {
        if (isEmpty()) error((char*)"스택 공백 에러");
        return data[top];
    }

    // 스택 내용 화면 출력 (p.26 + p.29 빈칸 완성)
    void display() {
        printf("[전체 학생의 수 = %2d]\n", top + 1);
        for (int i = 0; i <= top; i++)
            data[i].display();          // ← p.29 하이라이트된 빈칸
        printf("\n");
    }
};
