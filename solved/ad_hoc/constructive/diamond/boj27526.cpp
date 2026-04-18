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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, m, cnt;
string s; char last;
vector<string> v[2];

void print(string ss) {
    int i, j;
    for (i = 0; i < n; i++) {
        if (i % 2) {
            for (j = m - 1; j >= 0; j--) {
                cout << ss[i * m + j];
            }
        }
        else {
            for (j = 0; j < m; j++) {
                cout << ss[i * m + j];
            }
        }
        cout << '\n';
    }
}

void g(int i, string& sss) {
    int j;
    if (cnt & 1) {
        string ss = last + sss;
        v[i].emplace_back(ss);
        for (j = 1; j < ss.size(); j++) {
            swap(ss[j], ss[j - 1]);
            v[i].emplace_back(ss);
        }
    }
    else {
        string ss = sss + last;
        v[i].emplace_back(ss);
        for (j = ss.size() - 1; j > 0; j--) {
            swap(ss[j], ss[j - 1]);
            v[i].emplace_back(ss);
        }
    }
}

void solve() {
    int i, j, t = 0; cin >> n >> m;
    for (i = 1; i <= n; i++) {
        if (i % 2) {
            for (j = 1; j <= m; j++) {
                if (t + 1 == n * m) s += '#';
                else s += char(++t + '0');
            }
        }
        else {
            t += m;
            for (j = 1; j <= m; j++) {
                if (t == n * m) {
                    t--;
                    s += '#';
                }
                else s += char(t-- + '0');
            }
            t += m;
        }
    }
    string tmp = "";
    tmp += s[0];
    v[0].emplace_back(tmp);
    for (i = 1; i < n * m; i++) {
        last = s[i];
        for (auto& iter : v[(i - 1) % 2]) {
            cnt++;
            g(i % 2, iter);
        }
        tmp += s[i];
        v[(i - 1) % 2].clear();
    }
    reverse(v[(n * m - 1) % 2].begin(), v[(n * m - 1) % 2].end());
    for (auto& iter : v[(n * m - 1) % 2]) print(iter);
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
