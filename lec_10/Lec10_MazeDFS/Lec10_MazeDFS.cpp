// Lec10_MazeDFS.cpp
// 실습: Deque를 Stack으로 사용한 DFS 미로 탐색
// 교수님 코드 기반 (슬라이드 p.46~48)
// push_front + pop_front (LIFO)

#include <stdio.h>
#include <deque>
using namespace std;

const int ROWS = 6, COLS = 6;

// 교수님 제공 구조체 (p.46)
struct Location2D {
    int x;   // 행
    int y;   // 열
};

// 미로: 0=통로, 1=벽  (슬라이드 p.46 그림 기준)
// 입구: (1,0)  출구: (5,5)
int MAZE[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 1},
    {1, 1, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 0},
};

bool isValidLoc(int maze[][COLS], int r, int c) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return false;
    return maze[r][c] == 0;
}

void printMaze(int maze[][COLS]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++)
            printf("%2d", maze[r][c]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    printf("미로 구조 (0=통로, 1=벽, 입구=(1,0), 출구=(5,5)):\n");
    printMaze(MAZE);
    printf("[DFS] 미로 탐색 (슬라이드 p.48)\n");

    int maze[ROWS][COLS];
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            maze[r][c] = MAZE[r][c];

    deque<Location2D> locDeque;          // 교수님 코드: 위치 덱 객체
    Location2D entry = { 1, 0 };         // 입구 객체
    locDeque.push_front(entry);          // 덱에 입구 위치 삽입

    // 이웃 탐색 순서: 상/하/좌/우 (p.46)
    int dr[] = { -1,  1,  0,  0 };
    int dc[] = {  0,  0, -1,  1 };

    while (locDeque.empty() == false) {  // 덱이 비어있지 않는 동안
        Location2D here = locDeque.front(); // 덱의 front 상단 객체 복사
        locDeque.pop_front();               // 덱 상단 객체 삭제

        int r = here.x, c = here.y;
        printf("방문: (%d,%d)\n", r, c);

        if (r == ROWS - 1 && c == COLS - 1) {
            printf("출구 도착! (%d,%d)\n", r, c);
            return 0;
        }
        else {
            maze[r][c] = -1;   // 방문 표시
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (isValidLoc(maze, nr, nc)) {
                    Location2D next = { nr, nc };
                    locDeque.push_front(next);  // DFS: front에 push (Stack)
                }
            }
        }
    }
    printf("미로탐색실패\n");
    return 0;
}
