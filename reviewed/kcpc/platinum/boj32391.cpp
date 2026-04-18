#include<bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 1000000007
#define INF 1000000000000
using namespace std;

struct info {
    ll a, b, c;
};

struct cmp {
    bool operator()(info a, info b) {
        return a.c > b.c;
    }
};

ll n, x, y, f[2000001], fi[2000001];
vector<pll> v;
vector<vector<info>> g;
priority_queue<info, vector<info>, cmp> pq;

ll res(ll a, ll b) {
	ll ret = 1;
	while (b && a > 1){
        if (b&1) ret = ret * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return ret;
}

ll com(ll N, ll K) {
    return f[N] * fi[K] % MOD * fi[N - K] % MOD;
}

void dijkstra(ll st) {
    ll a, b, c;
    vector<ll> dis(n + 3, INF), cnt(n + 3, 0);
    cnt[st] = 1;
    dis[st] = 0;
    pq.push({st,1,0});
    while (!pq.empty()) {
        a = pq.top().a;
        b = pq.top().b;
        c = pq.top().c;
        pq.pop();
        if (dis[a] < c) continue;
        for (auto& iter : g[a]) {
            if (dis[iter.a] > dis[a] + iter.c) {
                dis[iter.a] = dis[a] + iter.c;
                cnt[iter.a] = cnt[a] * iter.b % MOD;
                pq.push({iter.a,cnt[iter.a],dis[iter.a]});
            }
            else if (dis[iter.a] == dis[a] + iter.c) {
                cnt[iter.a] += cnt[a] * iter.b % MOD;
                cnt[iter.a] %= MOD;
            }
        }
    }
    cout << cnt[n + 2];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, j; cin >> x >> y >> n;
    f[0] = 1;
    for (i = 1; i < 2000001; i++) f[i] = f[i - 1] * i % MOD;
    fi[2000000] = res(f[2000000], MOD - 2);
    for (i = 2000000; i > 0; i--) fi[i - 1] = fi[i] * i % MOD;
    v.resize(n + 1);
    g.resize(n + 3);
    for (i = 1; i <= n; i++) {
        cin >> v[i].x >> v[i].y;
        for (j = i - 1; j >= 1; j--) {
            if (v[i].x < v[j].x && v[i].y < v[j].y) {
                g[i].push_back({j,com(v[j].x - v[i].x + v[j].y - v[i].y - 2, v[j].x - v[i].x - 1),2 * (v[j].x - v[i].x + v[j].y - v[i].y - 2) + 1});
            }
            else if (v[i].x > v[j].x && v[i].y > v[j].y) {
                g[j].push_back({i,com(v[i].x - v[j].x + v[i].y - v[j].y - 2, v[i].x - v[j].x - 1),2 * (v[i].x - v[j].x + v[i].y - v[j].y - 2) + 1});
            }
        }
        g[n + 1].push_back({i,com(v[i].x + v[i].y, v[i].x),2 * (v[i].x + v[i].y)});
        g[i].push_back({n + 2,com(x - v[i].x + y - v[i].y - 2, x - v[i].x - 1),2 * (x - v[i].x + y - v[i].y - 2) + 1});
    }
    g[n + 1].push_back({n + 2,com(x + y, x),2 * (x + y)});
    dijkstra(n + 1);
}
