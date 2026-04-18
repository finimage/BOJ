#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 998244353
using namespace std;
 
void solve() {
    int i, n; cin >> n;
    if (n == 1) {
        cout << 1906;
        return;
    }
    if (n == 3) {
        cout << 2026;
        return;
    }
    if (n == 5) {
        cout << 10201 + 1905;
        return;
    }
    string s = "";
    s += '1';
    for (i = 1; i < n / 2; i++) s += '0';
    s += '2';
    for (i = 1; i < n / 2; i++) s += '0';
    s += '1';
    s[s.size() - 1] += 5;
    s[s.size() - 3] += 9;
    s[s.size() - 4] += 1;
    cout << s;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
