#include "MainWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QPainter>
#include <QMap>
#include <QVector>
#include <QPair>
#include <QSet>
#include <climits>

// ───────────────────────────────────────────
// 그래프 초기화 (전북대 캠퍼스 건물 - 고정값)
// ───────────────────────────────────────────
void MainWindow::initGraph() {

    // ── 노드: 건물 (코드, 이름, x좌표, y좌표) ──
    buildings["GR"] = {"GR", "정문",       60,  220};
    buildings["A1"] = {"A1", "공학관1호",  160,  140};
    buildings["A2"] = {"A2", "공학관2호",  260,  100};
    buildings["LB"] = {"LB", "중앙도서관", 260,  220};
    buildings["ST"] = {"ST", "학생회관",   160,  300};
    buildings["SC"] = {"SC", "자연과학관", 360,  160};
    buildings["GY"] = {"GY", "체육관",     360,  300};
    buildings["DM"] = {"DM", "진수당(학식)", 460, 220};

    // ── 간선: 양방향 연결 (거리: 미터) ──
    auto addEdge = [&](QString a, QString b, int dist) {
        graph[a].append({b, dist});
        graph[b].append({a, dist});
    };

    addEdge("GR", "A1", 200);
    addEdge("GR", "ST", 180);
    addEdge("A1", "A2", 150);
    addEdge("A1", "LB", 220);
    addEdge("A2", "SC", 180);
    addEdge("A2", "LB", 200);
    addEdge("LB", "ST", 160);
    addEdge("LB", "SC", 210);
    addEdge("LB", "GY", 250);
    addEdge("LB", "DM", 230);
    addEdge("ST", "GY", 200);
    addEdge("SC", "DM", 200);
    addEdge("GY", "DM", 180);
}

// ───────────────────────────────────────────
// 다익스트라 알고리즘
// ───────────────────────────────────────────
QMap<QString, int> MainWindow::dijkstra(const QString &start,
                                         QMap<QString, QString> &prev) {
    QMap<QString, int> dist;
    QSet<QString> visited;

    // 모든 노드 거리를 무한대로 초기화
    for (auto &key : buildings.keys()) {
        dist[key] = INT_MAX;
    }
    dist[start] = 0;
    prev[start] = "";

    // 미방문 노드 중 최소 거리 노드를 반복 선택
    while (visited.size() < buildings.size()) {
        // 현재 최소 거리 노드 선택
        QString u = "";
        int minDist = INT_MAX;
        for (auto &key : dist.keys()) {
            if (!visited.contains(key) && dist[key] < minDist) {
                minDist = dist[key];
                u = key;
            }
        }
        if (u.isEmpty()) break;
        visited.insert(u);

        // 인접 노드 거리 갱신
        for (const Edge &e : graph.value(u)) {
            if (!visited.contains(e.to)) {
                int newDist = dist[u] + e.distance;
                if (newDist < dist[e.to]) {
                    dist[e.to] = newDist;
                    prev[e.to] = u;  // 경로 추적
                }
            }
        }
    }
    return dist;
}

// ───────────────────────────────────────────
// 건물 노드 버튼 생성
// ───────────────────────────────────────────
void MainWindow::drawGraph(QWidget *cvs) {
    for (auto &b : buildings) {
        QPushButton *btn = new QPushButton(b.code, cvs);
        btn->setGeometry(b.x - 27, b.y - 27, 54, 54);
        btn->setStyleSheet(
            "QPushButton {"
            "  background-color: #2E7D32;"
            "  color: white;"
            "  border-radius: 27px;"
            "  font-weight: bold;"
            "  font-size: 11px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #43A047;"
            "}"
        );
        QString code = b.code;
        connect(btn, &QPushButton::clicked, this, [this, code]() {
            onBuildingClicked(code);
        });

        // 건물 이름 라벨
        QLabel *nameLabel = new QLabel(b.name, cvs);
        nameLabel->setStyleSheet("color: #CCFFCC; font-size: 10px;");
        nameLabel->move(b.x - 30, b.y + 28);
        nameLabel->resize(80, 16);
    }
}

// ───────────────────────────────────────────
// 생성자: UI 구성
// ───────────────────────────────────────────
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("🏫 캠퍼스 건물 간 최단 경로 탐색");
    resize(800, 520);

    initGraph();

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout *hLayout = new QHBoxLayout(central);

    // ── 왼쪽: 그래프 캔버스 ──
    canvas = new QWidget();
    canvas->setFixedSize(530, 480);
    canvas->setStyleSheet("background-color: #1B2618; border-radius: 8px;");
    drawGraph(canvas);

    // ── 오른쪽: 결과 패널 ──
    QWidget *panel = new QWidget();
    panel->setStyleSheet("background-color: #1A2320;");
    QVBoxLayout *vLayout = new QVBoxLayout(panel);

    infoLabel = new QLabel("건물을 클릭하세요\n해당 건물에서 다른 모든 건물까지의\n최단 경로를 보여줍니다.");
    infoLabel->setStyleSheet("color: white; font-size: 12px; padding: 8px;");
    infoLabel->setWordWrap(true);

    resultList = new QListWidget();
    resultList->setStyleSheet(
        "QListWidget { background-color: #162013; color: white; font-size: 12px; }"
        "QListWidget::item { padding: 6px; border-bottom: 1px solid #2a3a28; }"
        "QListWidget::item:selected { background-color: #2E7D32; }"
    );

    QLabel *hint = new QLabel("경로: 건물 코드 순서로 표시됩니다.");
    hint->setStyleSheet("color: #888; font-size: 10px; padding: 4px;");

    vLayout->addWidget(infoLabel);
    vLayout->addWidget(resultList);
    vLayout->addWidget(hint);

    hLayout->addWidget(canvas);
    hLayout->addWidget(panel);
}

// ───────────────────────────────────────────
// 캔버스에 간선(경로) 그리기
// ───────────────────────────────────────────
void MainWindow::paintEvent(QPaintEvent *) {
    // canvas 위에 직접 그리기 위해 canvas용 painter 사용
    QPainter painter(canvas);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor("#4CAF50"), 2));

    for (auto it = graph.begin(); it != graph.end(); ++it) {
        QString fromCode = it.key();
        Building from = buildings[fromCode];
        for (const Edge &e : it.value()) {
            Building to = buildings[e.to];
            painter.drawLine(from.x, from.y, to.x, to.y);

            // 거리 표시 (중간 지점)
            int mx = (from.x + to.x) / 2;
            int my = (from.y + to.y) / 2;
            painter.setPen(QColor("#AAFFAA"));
            painter.setFont(QFont("Arial", 8));
            painter.drawText(mx, my, QString("%1m").arg(e.distance));
            painter.setPen(QPen(QColor("#4CAF50"), 2));
        }
    }
}

// ───────────────────────────────────────────
// 슬롯: 건물 클릭 → 다익스트라 실행 → 결과 표시
// ───────────────────────────────────────────
void MainWindow::onBuildingClicked(const QString &code) {
    selectedBuilding = code;
    Building b = buildings[code];

    infoLabel->setText(
        QString("📍 출발지: %1 (%2)\n아래에서 각 건물까지의 최단 경로를 확인하세요.")
        .arg(b.name).arg(b.code)
    );

    // 다익스트라 실행
    QMap<QString, QString> prev;
    QMap<QString, int> dist = dijkstra(code, prev);

    resultList->clear();

    for (auto &key : buildings.keys()) {
        if (key == code) continue;

        Building target = buildings[key];

        // 경로 역추적
        QString path = "";
        QString cur = key;
        while (cur != "") {
            path = (path.isEmpty() ? cur : cur + " → ") + (path.isEmpty() ? "" : path);
            cur = prev.value(cur, "");
        }

        QString item;
        if (dist[key] == INT_MAX) {
            item = QString("🚫 %1 (%2) : 경로 없음").arg(target.name).arg(key);
        } else {
            item = QString("🏢 %1 (%2)\n   경로: %3\n   거리: %4m")
                   .arg(target.name)
                   .arg(key)
                   .arg(path)
                   .arg(dist[key]);
        }
        resultList->addItem(item);
    }

    canvas->update(); // 화면 갱신
}