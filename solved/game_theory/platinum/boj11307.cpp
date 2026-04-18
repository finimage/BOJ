#include<bits/stdc++.h>
using namespace std;

string s1, s2;

bool cmp(int a) {
    for (int i = 0; i < s2.size(); i++) {
        if (s1[a + i] != s2[i]) return 0;
    }
    return 1;
}

void solve() {
    int i, l1, l2, v; cin >> s1 >> s2;
    l1 = s1.size();
    l2 = s2.size();
    v = (l1 - l2) / 2;
    if (s1 == s2) cout << "Alice\n";
    else if (l1 % 2 == l2 % 2 && (cmp(v) || (cmp(v + 1) && cmp(v - 1)))) cout << "Alice\n";
    else if (l1 % 2 != l2 && cmp(v) && cmp(v + 1)) cout << "Alice\n";
    else cout << "Bob\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
