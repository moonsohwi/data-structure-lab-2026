// Lec10_MazeBFS.cpp
// 실습: Deque를 Queue로 사용한 BFS 미로 탐색
// 교수님 코드 기반 (슬라이드 p.49)
// push_back + pop_front (FIFO)

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
    printf("[BFS] 미로 탐색 (슬라이드 p.49)\n");

    int maze[ROWS][COLS];
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            maze[r][c] = MAZE[r][c];

    deque<Location2D> locDeque;
    Location2D entry = { 1, 0 };
    locDeque.push_back(entry);           // BFS: back에 삽입

    int dr[] = { -1,  1,  0,  0 };
    int dc[] = {  0,  0, -1,  1 };

    while (!locDeque.empty()) {
        Location2D here = locDeque.front();
        locDeque.pop_front();

        int r = here.x, c = here.y;
        printf("방문: (%d,%d)\n", r, c);

        if (r == ROWS - 1 && c == COLS - 1) {
            printf("출구 도착! (%d,%d)\n", r, c);
            return 0;
        }
        maze[r][c] = -1;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (isValidLoc(maze, nr, nc)) {
                Location2D next = { nr, nc };
                locDeque.push_back(next);  // BFS: back에 push (Queue)
            }
        }
    }
    printf("미로탐색실패\n");
    return 0;
}
