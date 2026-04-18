#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n;
string s;

void solve() {
    int i, j; cin >> n >> s;
    int st = -1, ed = -1;
    for (i = 0; i < n; i++) {
        if (s[i] == '1') {
            st = i;
            for (j = i + 1; j < n; j++) {
                if (s[j] == '0') {
                    ed = j - 1;
                    break;
                }
            }
            break;
        }
    }
    if (st == -1) {
        cout << "0\n";
    }
    else if (ed == -1) {
        if (st == 0) {
            for (i = st + 1; i < n; i++) cout << "1";
            cout << "0\n";
        }
        else {
            for (i = st; i < n; i++) cout << "1";
            cout << "\n";
        }
    }
    else {
        for (i = st; i <= ed; i++) {
            cout << "1";
        }
        int tmp = ed + 1;
        for (i = ed + 1; i < n; i++) {
            if (s[i] == '1') {
                tmp = i - 1;
                break;
            }
        }
        if (i == n) tmp = n - 1;
        while (tmp - ed < ed - st + 1) st++;
        for (i = ed + 1; i < n; i++) {
            int k = ((int)(s[st++] - '0') ^ (int)(s[i] - '0'));
            cout << k;
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
#endif
    int T; cin >> T;
    while (T--) solve();
}
