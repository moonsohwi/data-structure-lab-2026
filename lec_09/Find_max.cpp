#include <cstdio>

// 배열에서 최댓값을 찾는 함수
int findArrayMax(int score[], int n) {
    int tmp = score[0]; // 첫 번째 요소를 임시 최댓값으로 설정

    for (int i = 1; i < n; i++) { // 1번 인덱스부터 끝까지 비교
        if (score[i] > tmp) {
            tmp = score[i]; // 더 큰 값을 발견하면 tmp 갱신
        }
    }
    return tmp;
}

// 주 함수
int main() {
    int score[5] = { 1, 10, 2, 4, 5 };
    int out;

    out = findArrayMax(score, 5); // 함수 호출
    printf("result = %d", out);

    return 0;
}