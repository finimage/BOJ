#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, i; cin >> n;
    if (n == 2) {
        cout << "2 4 3";
        return 0;
    }
    if (n % 2) {
        int pp = 100000, mm = -100000;
        for (i = 3; i < n; i++) {
            if (i % 2) cout << pp++ << ' ';
            else cout << mm-- << ' ';
        }
        cout << n * n << ' ' << n << ' ' << 0 << ' ' << n + 1;
    }
    else {
        int pp = 100000, mm = -100000;
        for (i = 0; i < n; i++) {
            if (i % 2) cout << pp++ << ' ';
            else cout << mm-- << ' ';
        }
        cout << 0;
    }
}
