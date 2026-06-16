// WGraphDijkstra.cpp  (슬라이드 p.39 교수님 main 코드 그대로)
#include "WGraphDijkstra.h"

int main()
{
    WGraphDijkstra g;
    g.load("graph_sp.txt");
    // printf("Dijkstra의 최단경로 탐색을 위한 그래프: graph_sp.txt\n");
    // g.display();
    printf("Shortest Path By Dijkstra Algorithm\n");
    g.ShortestPath(0);      // 정점 0(A)에서 시작
    return 0;
}

/*
graph_sp.txt 파일 형식 (슬라이드 p.45 그래프 기준):
A-B:7, A-E:3, A-F:10, B-C:4, B-D:10, B-E:2, B-F:6 등

7
A 9999    7 9999 9999    3   10 9999
B    7 9999    4   10    2    6 9999
C 9999    4 9999    2 9999 9999 9999
D 9999   10    2 9999   11    9    4
E    3    2 9999   11 9999   13    5
F   10    6 9999    9   13 9999 9999
G 9999 9999 9999    4    5 9999 9999

예상 출력 (슬라이드 p.39):
Shortest Path By Dijkstra Algorithm
Step 1:    0    7 9999 9999    3   10 9999
Step 2:    0    5 9999   14    3   10    8
Step 3:    0    5    9   14    3   10    8
Step 4:    0    5    9   12    3   10    8
Step 5:    0    5    9   11    3   10    8
Step 6:    0    5    9   11    3   10    8
Step 7:    0    5    9   11    3   10    8
*/
