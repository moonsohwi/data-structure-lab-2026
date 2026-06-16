// Lec07_SequentialSearch.cpp
// 실습: Sequential Search (순차 탐색)
// 교수님 코드 기반 (슬라이드 p.10)

#include <stdio.h>

// 교수님 제공 코드 (p.10)
bool sequentialSearch(int arr[], int n, int item) {
    int  pos   = 0;
    bool found = false;
    while (pos < n && !found) {
        if (arr[pos] == item)
            found = true;
        else
            pos = pos + 1;
    }
    return found;
}

int main() {
    int arr[] = { 1, 4, 32, 10, 11, 19, 42, 13, 0, 12, 102 };
    int n     = sizeof(arr) / sizeof(arr[0]);

    // p.10 슬라이드 테스트 동일
    printf("search(3)   => %s\n", sequentialSearch(arr, n, 3)   ? "True" : "False");
    printf("search(13)  => %s\n", sequentialSearch(arr, n, 13)  ? "True" : "False");
    printf("search(102) => %s\n", sequentialSearch(arr, n, 102) ? "True" : "False");
    printf("search(99)  => %s\n", sequentialSearch(arr, n, 99)  ? "True" : "False");

    return 0;
}
