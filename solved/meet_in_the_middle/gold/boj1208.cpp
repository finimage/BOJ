#include<bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n, s;
int arr[41];
ll ans;
vector<int> v[2];

void bt(int st, int ed, int k, int val) {
    if (st == ed + 1) {
        v[k].emplace_back(val);
        return;
    }
    bt(st + 1, ed, k, val);
    bt(st + 1, ed, k, val + arr[st]);
}

int binary_search(int val) {
    int le = 0, ri = (int)v[1].size() - 1, mid, resri = -2, resle = -1;
    while (le <= ri) {
        mid = (le + ri) / 2;
        if (v[1][mid] + val <= s) {
            if (v[1][mid] + val == s) resri = mid;
            le = mid + 1;
        }
        else ri = mid - 1;
    }
    le = 0;
    ri = (int)v[1].size() - 1;
    while (le <= ri) {
        mid = (le + ri) / 2;
        if (v[1][mid] + val >= s) {
            if (v[1][mid] + val == s) resle = mid;
            ri = mid - 1;
        }
        else le = mid + 1;
    }
    //cout << resri << ' ' << resle << '\n'
    return resri - resle + 1;
}

void solve() {
    int i; cin >> n >> s;
    for (i = 1; i <= n; i++) cin >> arr[i];
    bt(1, n / 2, 0, 0);
    sort(v[0].begin(), v[0].end());
    bt(n / 2 + 1, n, 1, 0);
    sort(v[1].begin(), v[1].end());
    ll tmp = 0;
    for (i = 0; i < v[0].size(); i++) {
        if (i > 0 && v[0][i - 1] == v[0][i]) ans += tmp;
        else {
            tmp = binary_search(v[0][i]);
            ans += tmp;
        }
    }
    /*
    for (i = 0; i < v[0].size(); i++) cout << v[0][i] << ' ';
    cout << '\n';
    for (i = 0; i < v[1].size(); i++) cout << v[1][i] << ' ';
    cout << '\n';
    */
    cout << ans - (s == 0);
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
