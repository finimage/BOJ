#include<iostream>
#include<queue>
#define INF 50000001
using namespace std;

struct info {
    int x, y, dis, line;
};

struct cmp {
    bool operator()(const info& a, const info& b) {
        return a.dis > b.dis;
    }
};

int N, M, arr[501][501], dist[501][501], check[2][501], ans[501], dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 };
priority_queue<info, vector<info>, cmp> pq;

void init() {
    int i, j;
    for (i = 0; i < N; i++) {
        check[0][i] = INF;
        dist[i][M - 1] = arr[i][M - 1];
        pq.push({ i,M - 1,arr[i][M - 1],i });
        for (j = 0; j < M - 1; j++) dist[i][j] = INF;
    }
}

void dijkstra() {
    int a, b, dis, line, x, y, i;
    while (!pq.empty()) {
        a = pq.top().x;
        b = pq.top().y;
        dis = pq.top().dis;
        line = pq.top().line;
        pq.pop();
        if (dist[a][b] < dis) continue;
        if (b == 0) {
            if (check[0][a] > dis) {
                check[0][a] = dis;
                check[1][a] = line;
            }
        }
        for (i = 0; i < 4; i++) {
            x = a + dx[i];
            y = b + dy[i];
            if (0 <= x && x < N && 0 <= y && y < M) {
                if (dist[x][y] > dis + arr[x][y]) {
                    dist[x][y] = dis + arr[x][y];
                    pq.push({ x,y,dist[x][y],line });
                }
            }
        }
    }
    for (i = 0; i < N; i++) ans[check[1][i]]++;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j; cin >> N >> M;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) cin >> arr[i][j];
    }
    init();
    dijkstra();
    for (i = 0; i < N; i++) cout << ans[i] << '\n';
}
