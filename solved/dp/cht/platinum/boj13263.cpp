#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n;
ll A[100001], B[100001], dp[100001];
int v[100001], vl, vr;

ll cal(ll x) {
    while (vr - vl > 1 && vl < vr) {
        if (x * B[v[vl]] + dp[v[vl]] > x * B[v[vl + 1]] + dp[v[vl + 1]]) vl++;
        else break;
    }
    return x * B[v[vl]] + dp[v[vl]];
}

void upt(int ind) {
    while (vr - vl > 1) {
        int a = v[vr - 2], b = v[vr - 1];
        if ((double)(dp[b] - dp[a]) / (B[a] - B[b]) < (double)(dp[ind] - dp[a]) / (B[a] - B[ind])) break;
        vr--;
    }
    v[vr++] = ind;
}
 
void solve() {
    int i; cin >> n;
    for (i = 1; i <= n; i++) cin >> A[i];
    for (i = 1; i <= n; i++) cin >> B[i];
    v[0] = 1;
    vr = 1;
    for (i = 2; i <= n; i++) {
        dp[i] = cal(A[i]);
        upt(i);
    }
    cout << dp[n];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
