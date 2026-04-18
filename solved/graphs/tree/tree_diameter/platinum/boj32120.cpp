#include<bits/stdc++.h>
using namespace std;

int n, Q;
vector<vector<int>> g;
vector<int> dis, dist[3];
queue<int> q;

int bfs1(int st) {
    q.push(st);
    dis.clear();
    dis.resize(n + 1);
    dis[st] = 1;
    int i, a, d = 0;
    while (!q.empty()) {
        a = q.front();
        q.pop();
        for (auto& iter : g[a]) {
            if (dis[iter]) continue;
            q.push(iter);
            dis[iter] = dis[a] + 1;
        }
    }
    for (i = 1; i <= n; i++) {
        if (dis[i] > d) {
            d = dis[i];
            a = i;
        }
    }
    return a;
}

void bfs2(int st, int t) {
    q.push(st);
    dist[t][st] = 1;
    int a;
    while (!q.empty()) {
        a = q.front();
        q.pop();
        for (auto& iter : g[a]) {
            if (dist[t][iter]) continue;
            q.push(iter);
            dist[t][iter] = dist[t][a] + 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int i, a, b; cin >> n;
    g.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    int le = bfs1(1);
    int ri = bfs1(le);
    if (le > ri) swap(le, ri);
    cin >> Q;
    dist[0].resize(n + 1);
    bfs2(le, 0);
    dist[1].resize(n + 1);
    bfs2(ri, 1);
    int Max = 0, mid = 1;
    for (i = 1; i <= n; i++) {
        if (i == le || i == ri) continue;
        Max = max(Max, dist[0][i] + dist[1][i] - 2);
        if (Max == dist[0][i] + dist[1][i] - 2) mid = i;
    }
    dist[2].resize(n + 1);
    bfs2(mid, 2);
    while (Q--) {
        cin >> a >> b;
        cout << max(dist[0][a] + dist[0][b], max(dist[1][a] + dist[1][b], dist[2][a] + dist[2][b])) - 2 << '\n';
    }
}
