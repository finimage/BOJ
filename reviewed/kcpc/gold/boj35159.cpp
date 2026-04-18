#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n, kcnt, ccnt;
ll ans;
string s, ns;
 
void solve() {
    int i, cnt = 0; cin >> s;
    n = s.size();
    for (i = 0; i < n; i++) {
        if (s[i] == 'K') {
            ans += i - kcnt;
            ++kcnt;
        }
        else ns += s[i];
    }
    n -= kcnt;
    if (ns[0] == 'P') {
        for (i = 0; i < n; i++) {
            if (ns[i] == 'C') {
                ans += i;
                swap(ns[0], ns[i]);
                break;
            }
        }
    }
    if (ns[n - 1] == 'P') {
        for (i = n - 1; i >= 0; i--) {
            if (ns[i] == 'C') {
                ans += n - 1 - i;
                swap(ns[n - 1], ns[i]);
                break;
            }
        }
    }
    for (i = 1; i < n - 1; i++) {
        if (ns[i] == 'C') ++ccnt;
    }
    for (i = 1; i < n - 1; i++) {
        if (ns[i] == 'C') {
            ++cnt;
            ans += min(i - cnt, n - 2 - i - ccnt + cnt);
        }
    }
    cout << ans;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
