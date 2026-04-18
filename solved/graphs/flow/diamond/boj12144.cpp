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
    int to, cap, flow;
    edge(int _to, int _cap) : to(_to), cap(_cap), flow(0) {}
    int remain() {
        return cap - flow;
    }
    void add(int _flow) {
        flow += _flow;
    }
};

int n, sz, ans; string s;
vector<vector<string>> v;
vector<vector<int>> g;
vector<edge> e;
unordered_map<string, int> um;

void addedge(int u, int v, int c) {
    e.push_back(edge(v, c));
    e.push_back(edge(u, 0));
    g[u].push_back(e.size() -  2);
    g[v].push_back(e.size() -  1);
}

void bfs() {
    vector<bool> visited(sz * 2 + 2);
    visited[0] = 1;
    vector<int> pre(sz * 2 + 2, -1);
    vector<int> predge(sz * 2 + 2, -1);
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int a = q.front();
        q.pop();
        if (a == 1) break;
        for (auto& iter : g[a]) {
            if (!visited[e[iter].to] && e[iter].remain() > 0) {
                visited[e[iter].to] = 1;
                pre[e[iter].to] = a;
                predge[e[iter].to] = iter;
                q.push(e[iter].to);
            }
        }
    }
    if (!visited[1]) return;
    for (int i = 1; i; i = pre[i]) {
        e[predge[i]].add(1);
        e[predge[i]^1].add(-1);
    }
    ans++;
}

void max_flow() {
    ans = 0;
    while (1) {
        int k = ans;
        bfs();
        if (k == ans) break;
    }
    cout << ans << '\n';
}

void make_graph() {
    int i, j, t;
    sz = 0;
    um.clear();
    for (auto& iter : v) {
        for (auto& itr : iter) {
            if (!um.count(itr)) um[itr] = ++sz;
        }
    }
    e.clear();
    g.clear();
    g.resize(2 * sz + 2);
    int st = 0, ed = 1, INF = 100000;
    for (auto& iter : v[0]) {
        addedge(0, um[iter] * 2, INF);
    }
    for (auto& iter : v[1]) {
        addedge( um[iter] * 2 + 1, ed, INF);
    }
    for (i = 1; i <= sz; i++) {
        addedge( i * 2, i * 2 + 1, 1);
    }
    for (i = 2; i < n; i++) {
        for (j = 0; j < v[i].size(); j++) {
            for (t = j + 1; t < v[i].size(); t++) {
                int a = um[v[i][j]], b = um[v[i][t]];
                addedge(a * 2 + 1, b * 2, INF);
                addedge(b * 2 + 1, a * 2, INF);
            }
        }
    }
}

void solve() {
    int i, j; cin >> n;
    cin.ignore();
    string tmp = "";
    v.clear();
    v.resize(n);
    for (j = 0; j < n; j++) {
        getline(cin, s);
        for (i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                if (tmp == "") continue;
                v[j].push_back(tmp);
                tmp = "";
            }
            else if (i + 1 == s.size()) {
                tmp += s[i];
                v[j].push_back(tmp);
                tmp = "";
            }
            else tmp += s[i];
        }
    }
    make_graph();
    max_flow();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 1; cin >> T;
    //while (T--) solve();
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
