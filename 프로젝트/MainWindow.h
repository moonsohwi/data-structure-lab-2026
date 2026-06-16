#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QVector>
#include <QString>
#include <QPair>

// 건물 정보 구조체 (그래프 노드)
struct Building {
    QString code;   // 건물 코드 (예: "A1")
    QString name;   // 건물 이름 (예: "공학관")
    int x, y;       // 화면 상 위치
};

// 간선 정보 구조체
struct Edge {
    QString to;     // 도착 건물 코드
    int distance;   // 거리 (미터)
};

class QLabel;
class QListWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onBuildingClicked(const QString &code);

private:
    void initGraph();
    void drawGraph(QWidget *canvas);

    // 다익스트라 알고리즘
    // 반환값: 각 노드까지의 최단 거리 + 이전 노드 (경로 추적용)
    QMap<QString, int> dijkstra(const QString &start,
                                 QMap<QString, QString> &prev);

    // 그래프 데이터
    QMap<QString, Building> buildings;          // 노드
    QMap<QString, QVector<Edge>> graph;         // 인접 리스트

    // UI
    QLabel *infoLabel;
    QListWidget *resultList;
    QString selectedBuilding;

    QWidget *canvas;
};

#endif // MAINWINDOW_H