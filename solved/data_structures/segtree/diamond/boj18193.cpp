#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define INF 987654321987654321
using namespace std;

int n, m, k, cnt, tree[1000004][2];
vector<vector<pll>> g;
vector<ll> dist;
priority_queue<pll> pq;

int init1(int start, int end, int ind) {
    if (start == end) return tree[ind][0] = start;
    int mid = (start + end) / 2;
    int le = init1(start, mid, ind * 2);
    int ri = init1(mid + 1, end, ind * 2 + 1);
    cnt++;
    g[le].push_back({cnt,0});
    g[ri].push_back({cnt,0});
    return tree[ind][0] = cnt;
}

int init2(int start, int end, int ind) {
    if (start == end) return tree[ind][1] = start;
    int mid = (start + end) / 2;
    int le = init2(start, mid, ind * 2);
    int ri = init2(mid + 1, end, ind * 2 + 1);
    cnt++;
    g[cnt].push_back({le,0});
    g[cnt].push_back({ri,0});
    return tree[ind][1] = cnt;
}

void res1(int start, int end, int ind, int le, int ri, int node, ll val) {
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        g[tree[ind][0]].push_back({node,val});
        return;
    }
    int mid = (start + end) / 2;
    res1(start, mid, ind * 2, le, ri, node, val);
    res1(mid + 1, end, ind * 2 + 1, le, ri, node, val);
}

void res2(int start, int end, int ind, int le, int ri, int node, ll val) {
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        g[node].push_back({tree[ind][1],val});
        return;
    }
    int mid = (start + end) / 2;
    res2(start, mid, ind * 2, le, ri, node, val);
    res2(mid + 1, end, ind * 2 + 1, le, ri, node, val);
}

void dijkstra(int st) {
    dist.resize(cnt + 1, INF);
    dist[st] = 0;
    pq.push({0,st});
    while (!pq.empty()) {
        ll a = -pq.top().x;
        ll b = pq.top().y;
        pq.pop();
        for (auto& iter : g[b]) {
            if (dist[iter.x] > iter.y + a) {
                dist[iter.x] = iter.y + a;
                pq.push({-dist[iter.x],iter.x});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
#endif
    int i, a, b, c, d, e; cin >> n >> m >> k;
    g.resize(10 * n + 2 * m + 1);
    cnt = n;
    init1(1, n, 1);
    init2(1, n, 1);
    for (i = 0; i < m; i++) {
        cin >> a >> b >> c >> d >> e;
        cnt++;
        res1(1, n, 1, b, c, cnt, 0);
        cnt++;
        res2(1, n, 1, d, e, cnt, 0);
        g[cnt - 1].push_back({cnt, a});
    }
    dijkstra(k);
    for (i = 1; i <= n; i++) {
        if (dist[i] == INF) cout << -1 << ' ';
        else cout << dist[i] << ' ';
    }
}
