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

int n, alp[27][2];
string s;

void solve() {
    int i; char c; cin >> n >> c >> s;
    sort(s.begin(), s.end());
    for (auto& iter : s) {
        if (iter >= 'a') alp[iter - 'a'][1]++;
        else alp[iter - 'A'][0]++;
    }
    if (s[0] == c) {
        if (alp[c - 'A'][1]) {
            int tf = 1, ttf = 1;
            for (auto& iter : s) {
                if (tf) {
                    if (iter == c) cout << iter;
                    else if (iter != c - 'A' + 'a') {
                        cout << (char)(c - 'A' + 'a') << iter;
                        tf = 0;
                    }
                    else {
                        cout << iter;
                        tf = ttf = 0;
                    }
                }
                else if (ttf) {
                    if (iter != c - 'A' + 'a') cout << iter;
                    else ttf = 0;
                }
                else cout << iter;
            }
        }
        else cout << s;
    }
    else {
        if (alp[c - 'A'][1] >= 2) {
            int tf = 1;
            for (auto& iter : s) {
                if (iter != c) {
                    if (iter != c - 'A' + 'a') cout << iter;
                    else {
                        cout << iter;
                        if (tf) {
                            tf = 0;
                            for (i = 0; i < alp[c - 'A'][0]; i++) cout << c;
                        }
                    }
                }
            }
        }
        else if (alp[c - 'A'][1] == 1) {
            for (auto& iter : s) {
                if (iter != c && iter != c - 'A' + 'a') cout << iter;
            }
            cout << (char)(c - 'A' + 'a');
            for (i = 0; i < alp[c - 'A'][0]; i++) cout << c;
        }
        else {
            for (auto& iter : s) {
                if (iter != c) cout << iter;
            }
            for (i = 0; i < alp[c - 'A'][0]; i++) cout << c;
        }
    }
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
