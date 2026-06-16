import sys

## 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt')
N, M = list(map(int,input().split()))
print(N, M)
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)
###################################


def count_stages(concerts):
    """
    콘서트장 약도(2D 격자)에서 독립적인 무대 공간의 개수를 반환하는 함수.

    무대 공간의 정의:
        - 콘서트장은 N x M 크기의 격자로 이루어져 있다.
        - 펜스(1)가 없는 빈 공간(0)들이 상하좌우로 연결되어 있으면 하나의 무대 공간을 이룬다.
        - 즉, 0으로 이루어진 연결 요소(Connected Component)의 개수를 세면 된다.

    풀이 방법 (BFS):
        - 격자 전체를 순회하면서 아직 방문하지 않은 빈 공간(0)을 발견하면,
          그 지점에서 BFS를 시작하여 연결된 모든 0을 방문 처리한다.
        - BFS를 한 번 수행할 때마다 독립적인 무대 공간 1개를 발견한 것이므로,
          BFS 호출 횟수가 곧 무대 공간의 개수가 된다.

    Args:
        concerts (list of list of int): N x M 크기의 2D 정수 배열.
                                        0 = 빈 공간, 1 = 펜스

    Returns:
        int: 독립적인 무대 공간(0으로 연결된 영역)의 총 개수.
    """
    n = len(concerts)       # 행(row) 수
    m = len(concerts[0])    # 열(column) 수

    # 방문 여부를 기록하는 2D 배열 (False: 미방문, True: 방문 완료)
    visited = [[False] * m for _ in range(n)]

    # 상하좌우 4방향 이동 벡터 (행 변화량, 열 변화량)
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    def bfs(start_r, start_c):
        """
        (start_r, start_c)에서 시작하여 연결된 모든 빈 공간(0)을 BFS로 방문 처리.

        큐에 시작 좌표를 넣고, 상하좌우 인접 셀 중 빈 공간이면서 미방문인 셀을
        순서대로 큐에 추가하며 탐색한다.

        Args:
            start_r (int): 탐색 시작 행 인덱스.
            start_c (int): 탐색 시작 열 인덱스.
        """
        queue = [(start_r, start_c)]
        visited[start_r][start_c] = True

        while queue:
            r, c = queue.pop(0)    # 큐 앞에서 꺼냄 (FIFO)

            # 4방향 인접 셀 탐색
            for dr, dc in directions:
                nr, nc = r + dr, c + dc

                # 격자 범위 내에 있고, 빈 공간(0)이며, 아직 방문하지 않은 경우
                if 0 <= nr < n and 0 <= nc < m:
                    if concerts[nr][nc] == 0 and not visited[nr][nc]:
                        visited[nr][nc] = True    # 큐 삽입 시 방문 표시 (중복 방지)
                        queue.append((nr, nc))

    answer = 0  # 독립 무대 공간 개수

    # 격자 전체를 순회하며 탐색 시작점 탐색
    for r in range(n):
        for c in range(m):
            # 아직 방문하지 않은 빈 공간(0) 발견 -> 새로운 무대 공간 시작
            if concerts[r][c] == 0 and not visited[r][c]:
                bfs(r, c)     # 연결된 모든 빈 공간 방문 처리
                answer += 1   # 무대 공간 1개 발견

    return answer


print(count_stages(concerts))
