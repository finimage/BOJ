#include<bits/stdc++.h>
#define ld long double
#define pii pair<int, int>
#define pldi pair<ld, int>
#define pld pair<ld, ld>
#define x first
#define y second
#define INF 2000000000000
using namespace std;

int n, start_, end_; pii tmp;
vector<vector<pldi>> g;
vector<pii> v;
vector<ld> dist;
priority_queue<pldi> pq;

void dijkstra(int a) {
    dist.resize(n + 1, (ld)INF);
    dist[a] = 0;
    pq.push({0,a});
    while (!pq.empty()) {
        a = pq.top().y;
        ld b = -pq.top().x;
        pq.pop();
        if (dist[a] < b) continue;
        for (auto& iter : g[a]) {
            if (dist[iter.y] > b + iter.x) {
                dist[iter.y] = b + iter.x;
                pq.push({-dist[iter.y],iter.y});
            }
        }
    }
}

ld dis(pld a, pld b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void solve() {
    int i, j, b, c, tf = 0; cin >> tmp.x >> tmp.y >> n;
    for (i = 0; i < n; i++) {
        cin >> b >> c;
        if (b == 0 && c == 0) {
            start_ = i + 1;
            tf |= 2;
        }
        if (b == tmp.x && c == tmp.y) {
            end_ = i + 1;
            tf |= 1;
        }
        v.push_back({b,c});
    }
    if (tf == 0) {
        v.push_back({0,0});
        start_ = n + 1;
        v.push_back(tmp);
        end_ = n + 2;
        n += 2;
    }
    else if (tf == 1) {
        v.push_back({0,0});
        start_ = n + 1;
        n++;
    }
    else if (tf == 2) {
        v.push_back(tmp);
        end_ = n + 1;
        n++;
    }
    g.resize(n + 1);
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            ld d = dis(v[i], v[j]), k = 2;
            if ((i + 1 == start_ || j + 1 == start_) && (tf & 2) == 0) k--;
            if ((i + 1 == end_ || j + 1 == end_) && (tf & 1) == 0) k--;
            pldi ttmp = {(d - k > 0 ? d - k : 0),j + 1};
            g[i + 1].emplace_back(ttmp);
            ttmp.y = i + 1;
            g[j + 1].emplace_back(ttmp);
        }
    }
    dijkstra(start_);
    //for (i = 1; i <= n; i++) cout << i << ' ' << dist[i] << '\n';
    cout << fixed << setprecision(15) << dist[end_];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 1; //cin >> T;
    while (T--) solve();
}
