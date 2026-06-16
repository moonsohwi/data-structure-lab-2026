// WGraphDijkstra.h
// 슬라이드 p.37~38: Dijkstra 최단경로 알고리즘
// WGraphMST.h 의 AdjMatGraph, WGraph 구조 동일하게 사용

#pragma once
#include <cstdio>
#include <cstdlib>

#define INF      9999
#define MAX_VTXS 100

// ── AdjMatGraph (WGraphMST.h와 동일한 기반 클래스) ───────────
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
            for (int j = 0; j < size; j++)
                printf("%5d ", adj[i][j]);
            printf("\n");
        }
    }
};

// ── WGraph (p.5) ──────────────────────────────────────────
class WGraph : public AdjMatGraph {
public:
    void insertEdge(int u, int v, int weight) {
        if (weight > INF) weight = INF;
        setEdge(u, v, weight);
    }
    bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }
};

// ── WGraphDijkstra: Dijkstra 최단경로 (슬라이드 p.37~38) ────
class WGraphDijkstra : public WGraph {
    int  dist[MAX_VTXS];    // 시작노드로부터의 최단경로 거리 (p.37)
    bool found[MAX_VTXS];   // 방문한 정점 표시 (p.37)
public:
    // 방문 안 한 정점 중 dist 최솟값 정점 선택 (p.37)
    int chooseVertex() {
        int min    = INF;
        int minpos = -1;
        for (int i = 0; i < size; i++)
            if (dist[i] < min && !found[i]) {
                min    = dist[i];
                minpos = i;
            }
        return minpos;
    }

    // dist 상태를 출력하는 함수 (p.37)
    void printDistance() {
        for (int i = 0; i < size; i++)
            printf("%5d", dist[i]);
        printf("\n");
    }

    // Dijkstra 최단경로 알고리즘: start 정점에서 시작 (p.38)
    void ShortestPath(int start) {
        for (int i = 0; i < size; i++) {
            dist[i]  = getEdge(start, i);
            found[i] = false;
        }
        found[start] = true;    // 시작노드 방문 표시
        dist[start]  = 0;       // 최초 거리

        for (int i = 0; i < size; i++) {
            printf("Step%2d:", i + 1);
            printDistance();
            int u    = chooseVertex();
            found[u] = true;
            for (int w = 0; w < size; w++) {
                if (found[w] == false)
                    if (dist[u] + getEdge(u, w) < dist[w])
                        dist[w] = dist[u] + getEdge(u, w);
            }
        }
    }
};
