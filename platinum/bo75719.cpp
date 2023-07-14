#include<iostream>
#include<queue>
#include<vector>
#define INF 10000001
using namespace std;

struct info {
    int x, dis;
};

struct cmp {
    bool operator()(const info& a, const info& b) {
        return a.dis > b.dis;
    }
};

int n, m, dis[501];
bool visited[501], link[501][501];
priority_queue<info, vector<info>, cmp> pq;
vector<info> graph[501];
vector<int> path[501];

void init(int end) {
    int i, a;
    queue<int> q;
    q.push(end);
    visited[end] = 0;
    while (!q.empty()) {
        a = q.front();
        q.pop();
        for (auto iter = path[a].begin(); iter != path[a].end(); iter++) {
            link[*iter][a] = 0;
            if (!visited[*iter]) continue;
            visited[*iter] = 0;
            q.push(*iter);
        }
    }
    for (i = 0; i < n; i++) {
        graph[i].clear();
        path[i].clear();
    }
}

void solve(int start, int mark) {
    int x, dist, i;
    for (i = 0; i <= n; i++) dis[i] = INF;
    dis[start] = 0;
    pq.push({ start,0 });
    while (!pq.empty()) {
        x = pq.top().x;
        dist = pq.top().dis;
        pq.pop();
        if (dist > dis[x]) continue;
        for (auto iter = graph[x].begin(); iter != graph[x].end(); iter++) {
            if (link[x][iter->x]) continue;
            if (mark && dis[iter->x] == dist + iter->dis) {
                path[iter->x].push_back(x);
            }
            if (dis[iter->x] > dist + iter->dis) {
                dis[iter->x] = dist + iter->dis;
                pq.push({ iter->x,dis[iter->x] });
                if (mark) {
                    path[iter->x].clear();
                    path[iter->x].push_back(x);
                }
            }
        }
    }
}

void remove(int end) {
    int a;
    queue<int> q;
    q.push(end);
    visited[end] = 1;
    while (!q.empty()) {
        a = q.front();
        q.pop();
        for (auto iter = path[a].begin(); iter != path[a].end(); iter++) {
            link[*iter][a] = 1;
            if (visited[*iter]) continue;
            visited[*iter] = 1;
            q.push(*iter);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int s, d, u, v, p, i;
    while (1) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        cin >> s >> d;
        for (i = 0; i < m; i++) {
            cin >> u >> v >> p;
            graph[u].push_back({ v,p });
        }
        solve(s, 1);
        remove(d);
        solve(s, 0);
        if (dis[d] == INF) cout << -1 << '\n';
        else cout << dis[d] << '\n';
        init(d);
    }
}
