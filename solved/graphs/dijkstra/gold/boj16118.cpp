#include<iostream>
#include<queue>
#include<vector>
#define INF 2000000000001
#define ll long long
using namespace std;

struct wolf {
    ll dis;
    int x, check;
};

struct fox {
    ll dis;
    int x;
};

struct cmp_w {
    bool operator()(const wolf& w1, const wolf& w2) {
        return w1.dis > w2.dis;
    }
};

struct cmp_f {
    bool operator()(const fox& f1, const fox& f2) {
        return f1.dis > f2.dis;
    }
};

priority_queue<wolf, vector<wolf>, cmp_w> wo;
priority_queue<fox, vector<fox>, cmp_f> fo;
vector<pair<int, ll>> v[4001];
ll fox_dis[4001], wolf_dis[2][4001];

ll min_(ll a, ll b) {
    return (a < b) ? a : b;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, i, x, y, ans = 0; cin >> n >> m;
    ll dis;
    for (i = 1; i <= n; i++) fox_dis[i] = wolf_dis[0][i] = wolf_dis[1][i] = INF;
    fox_dis[1] = wolf_dis[0][1] = 0;
    for (i = 0; i < m; i++) {
        cin >> x >> y >> dis;
        v[x].push_back({ y,dis * 2 });
        v[y].push_back({ x,dis * 2 });
    }
    wo.push({ 0,1,1 });
    while (!wo.empty()) {
        dis = wo.top().dis;
        x = wo.top().x;
        y = wo.top().check;
        wo.pop();
        if (dis > wolf_dis[(y) ? 0 : 1][x]) continue;
        for (auto iter = v[x].begin(); iter != v[x].end(); iter++) {
            if (wolf_dis[y][iter->first] > dis + iter->second / ((y) ? 2 : 0.5)) {
                wolf_dis[y][iter->first] = dis + iter->second / ((y) ? 2 : 0.5);
                wo.push({ wolf_dis[y][iter->first], iter->first, (y) ? 0 : 1 });
            }
        }
    }
    fo.push({ 0,1 });
    while (!fo.empty()) {
        dis = fo.top().dis;
        x = fo.top().x;
        fo.pop();
        if (dis > fox_dis[x]) continue;
        for (auto iter = v[x].begin(); iter != v[x].end(); iter++) {
            if (fox_dis[iter->first] > dis + iter->second) {
                fox_dis[iter->first] = dis + iter->second;
                fo.push({ fox_dis[iter->first], iter->first });
            }
        }
    }
    for (i = 2; i <= n; i++) {
        if (fox_dis[i] < min_(wolf_dis[0][i], wolf_dis[1][i])) ans++;
    }
    cout << ans;
}
