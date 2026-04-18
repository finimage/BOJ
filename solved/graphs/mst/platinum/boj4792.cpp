#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 998244353
using namespace std;

struct edge {
    ll a, b, c;
    bool operator<(const edge& x) const {
        return c > x.c;
    }
};

ll n, m, k;
vector<pii> blue, red;
vector<int> par;
priority_queue<edge> pq;

ll find_(ll a) {
    if (a == par[a]) return a;
    return par[a] = find_(par[a]);
}

bool union_(ll a, ll b) {
    a = find_(a);
    b = find_(b);
    if (a == b) return 1;
    if (a > b) swap(a, b);
    par[a] = b;
    return 0;
}

ll mst() {
    ll a, b, c, i, ans = 0;
    par.resize(n + 1);
    for (i = 1; i <= n; i++) par[i] = i;
    while (!pq.empty()) {
        auto [a, b, c] = pq.top();
        pq.pop();
        if (union_(a, b)) continue;
        ans += c;
    }
    par.clear();
    return ans - n + 1;
}

void solve() {
    ll i, a, b; char c;
    for (i = 0; i < m; i++) {
        cin >> c >> a >> b;
        if (c == 'B') blue.push_back({a,b});
        else red.push_back({a,b});
    }
    for (auto& iter : blue) pq.push({iter.x,iter.y,2});
    for (auto& iter : red) pq.push({iter.x,iter.y,1});
    ll Min = mst();
    for (auto& iter : blue) pq.push({iter.x,iter.y,1});
    for (auto& iter : red) pq.push({iter.x,iter.y,2});
    ll Max = n - 1 - mst();
    if (Min <= k && k <= Max) cout << "1\n";
    else cout << "0\n";
    blue.clear();
    red.clear();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    //int T = 1; //cin >> T;
    while (1) {
        cin >> n >> m >> k;
        if (n == 0 && m == 0 && k == 0) break;
        solve();
    }
}
