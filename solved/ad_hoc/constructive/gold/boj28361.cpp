#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

void solve() {
    int n, i; cin >> n;
    cout << n << '\n';
    vector<int> v = {3,2,4};
    if (n % 3 == 2) {
        v = {4,3,5};
        cout << 1 << ' ' << 2 << ' ';
        for (i = 0; i < n / 3; i++) {
            cout << v[0] + i * 3 << ' ';
            cout << v[1] + i * 3 << ' ';
            cout << v[2] + i * 3 << ' ';
        }
        cout << 1;
    }
    else if (n % 3 == 1) {
        cout << 1 << ' ';
        for (i = 0; i < n / 3; i++) {
            cout << v[0] + i * 3 << ' ';
            cout << v[1] + i * 3 << ' ';
            cout << v[2] + i * 3 << ' ';
        }
        cout << 1;
    }
    else {
        cout << 1 << ' ';
        for (i = 0; i < n / 3 - 1; i++) {
            cout << v[0] + i * 3 << ' ';
            cout << v[1] + i * 3 << ' ';
            cout << v[2] + i * 3 << ' ';
        }
        cout << n << ' ';
        cout << n - 1 << ' ';
        cout << 1;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
