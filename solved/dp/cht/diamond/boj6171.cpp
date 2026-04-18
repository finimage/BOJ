#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n;
pll wh[50001];
ll A[50001], B[50001], dp[50001];
vector<int> v;

ll cal(ll x) {
    int le = 1, ri = v.size() - 1, mid, res = 0;
    while (le <= ri) {
        mid = (le + ri) / 2;
        int a = v[mid - 1], b = v[mid];
        if ((double)(dp[b] - dp[a]) / (B[a] - B[b]) < x) {
            res = mid;
            le = mid + 1;
        }
        else ri = mid - 1;
    }
    return x * B[v[res]] + dp[v[res]];
}

void upt(int ind) {
    while (v.size() > 1) {
        int a = v[v.size() - 2], b = v.back();
        if ((double)(dp[b] - dp[a]) / (B[a] - B[b]) < (double)(dp[ind] - dp[a]) / (B[a] - B[ind])) break;
        v.pop_back();
    }
    v.push_back(ind);
}
 
void solve() {
    int i; cin >> n;
    for (i = 1; i <= n; i++) cin >> wh[i].x >> wh[i].y;
    sort(wh + 1, wh + n + 1, greater<pll>());
    for (i = 1; i <= n; i++) {
        B[i] = i == n ? 0 : wh[i + 1].x;
        A[i] = max(wh[i].y, i == 1 ? 0 : A[i - 1]);
    }
    v.push_back(1);
    dp[1] = wh[1].x * wh[1].y;
    for (i = 2; i <= n; i++) {
        dp[i] = min(wh[1].x * A[i], cal(A[i]));
        upt(i);
    }
    cout << dp[n];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
