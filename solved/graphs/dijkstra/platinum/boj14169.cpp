#include<bits/stdc++.h>
#define pii pair<int, int>
#define x first
#define y second
#define INF 100000000
using namespace std;

struct info {
    int x, y, d;
};

bool cmp1(info a, info b) {
    if (a.x < b.x) return 1;
    if (a.x == b.x && a.y < b.y) return 1;
    return 0;
}

bool cmp2(info a, info b) {
    if (a.y < b.y) return 1;
    if (a.y == b.y && a.x < b.x) return 1;
    return 0;
}

struct comp {
    bool operator()(info& a, info& b) {
        return a.y > b.y;
    }
};

int n;
vector<info> v;
vector<vector<pii>> g;
vector<int> dis[4];
priority_queue<info, vector<info>, comp> pq;

void dijkstra() {
    pq.push({1,0,0});
    pq.push({1,0,1});
    pq.push({1,0,2});
    pq.push({1,0,3});
    int a, b, c;
    while (!pq.empty()) {
        a = pq.top().x;
        b = pq.top().y;
        c = pq.top().d;
        pq.pop();
        if (dis[c][a] < b) continue;
        for (auto& iter : g[a]) {
            int k;
            if (c == iter.y) k = 0;
            else if (c % 2 == iter.y % 2) continue;
            else k = 1;
            if (dis[iter.y][iter.x] > b + k) {
                dis[iter.y][iter.x] = b + k;
                pq.push({iter.x,dis[iter.y][iter.x],iter.y});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i; cin >> n;
    n += 2;
    v.resize(n + 1);
    g.resize(n + 1);
    for (i = 1; i <= n; i++) {
        cin >> v[i].x >> v[i].y;
        v[i].d = i;
    }
    sort(v.begin() + 1, v.end(), cmp1);
    for (i = 2; i <= n; i++) {
        if (v[i].x == v[i - 1].x) {
            g[v[i].d].push_back({v[i-1].d,0});
            g[v[i-1].d].push_back({v[i].d,2});
        }
    }
    sort(v.begin() + 1, v.end(), cmp2);
    for (i = 2; i <= n; i++) {
        if (v[i].y == v[i - 1].y) {
            g[v[i].d].push_back({v[i-1].d,1});
            g[v[i-1].d].push_back({v[i].d,3});
        }
    }
    for (i = 0; i < 4; i++) {
        dis[i].resize(n + 1, INF);
        dis[i][1] = 0;
    }
    dijkstra();
    int ans = INF;
    for (i = 0; i < 4; i++) ans = min(ans, dis[i][2]);
    cout << (ans == INF ? -1 : ans);
}
