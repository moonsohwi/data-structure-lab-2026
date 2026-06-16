// WGraphFloyd.h
// 슬라이드 p.43~44: Floyd 최단경로 알고리즘

#pragma once
#include <cstdio>
#include <cstdlib>

#define INF      9999
#define MAX_VTXS 100

// ── AdjMatGraph ───────────────────────────────────────────
class AdjMatGraph {
protected:
    int  size;
    char vname[MAX_VTXS];
    int  adj[MAX_VTXS][MAX_VTXS];
public:
    AdjMatGraph() { reset(); }
    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                adj[i][j] = 0;
    }
    char getVertex(int i)               { return vname[i]; }
    int  getEdge(int i, int j)          { return adj[i][j]; }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }
    bool isEmpty() { return size == 0; }
    bool isFull()  { return size >= MAX_VTXS; }

    void insertVertex(char name) {
        if (isFull()) { printf("그래프 정점 개수 초과\n"); return; }
        vname[size++] = name;
    }

    void load(char* filename) {
        FILE* fp = fopen(filename, "r");
        if (fp != NULL) {
            int n, val;
            fscanf(fp, "%d", &n);
            for (int i = 0; i < n; i++) {
                char str[80];
                fscanf(fp, "%s", str);
                insertVertex(str[0]);
                for (int j = 0; j < n; j++) {
                    fscanf(fp, "%d", &val);
                    setEdge(i, j, val);
                }
            }
            fclose(fp);
        }
    }

    void display() {
        printf("%d\n", size);
        for (int i = 0; i < size; i++) {
            printf("%c  ", vname[i]);
            for (int j = 0; j < size; j++) {
                if (adj[i][j] >= INF) printf("  - ");
                else                  printf("%3d ", adj[i][j]);
            }
            printf("\n");
        }
    }
};

// ── WGraph ────────────────────────────────────────────────
class WGraph : public AdjMatGraph {
public:
    void insertEdge(int u, int v, int weight) {
        if (weight > INF) weight = INF;
        setEdge(u, v, weight);
    }
    bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }
};

// ── WGraphFloyd: Floyd 최단경로 (슬라이드 p.43~44) ──────────
class WGraphFloyd : public WGraph {
    int A[MAX_VTXS][MAX_VTXS];     // 최단경로 거리 (p.43)
public:
    // 단계별 A 행렬 출력 (p.44)
    void printA() {
        printf("=====================================\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (A[i][j] == INF) printf(" INF ");
                else                printf("%4d ", A[i][j]);
            }
            printf("\n");
        }
    }

    // Floyd 알고리즘 (p.43)
    void ShortestPathFloyd() {
        // 초기화: A를 인접행렬 값으로 설정
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                A[i][j] = getEdge(i, j);

        // Floyd 3중 반복문
        for (int k = 0; k < size; k++) {
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    if (A[i][k] + A[k][j] < A[i][j])
                        A[i][j] = A[i][k] + A[k][j];
            printA();   // 단계별 출력 (p.43)
        }
    }
};
