// 12장-WGraphFloyd.cpp  (슬라이드 p.45 구조 기반)
// Floyd 알고리즘 main: graph_sp.txt에서 그래프 로드 후 Floyd 실행
#include "WGraphFloyd.h"

int main()
{
    WGraphFloyd g;
    g.load("wgraph_sp.txt");
    // printf("최단거리(wgraph_sp.txt)\n");
    // g.display();
    printf("Shortest Path By Floyd Algorithm\n");
    g.ShortestPathFloyd();
    return 0;
}

/*
wgraph_sp.txt 파일 형식 (슬라이드 p.45 그래프: A B C D E F G 기준):
A-B:7, A-E:3, A-F:10, B-C:4, B-D:10, B-E:2, B-F:6, C-D:2, D-E:11, D-F:9, D-G:4, E-F:13, E-G:5

7
A    0    7 9999 9999    3   10 9999
B    7    0    4   10    2    6 9999
C 9999    4    0    2 9999 9999 9999
D 9999   10    2    0   11    9    4
E    3    2 9999   11    0   13    5
F   10    6 9999    9   13    0 9999
G 9999 9999 9999    4    5 9999    0

예상 출력 (슬라이드 p.45):
Floyd 알고리즘이 k=0~6 단계별로 A 행렬을 갱신하며 출력
최종 결과: 모든 정점 쌍의 최단경로
  A  B  C  D  E  F  G
A 0  5  9  11  3  10  8
B 5  0  4  6   2  6   7
...
*/
