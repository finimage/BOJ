#include<bits/stdc++.h>
using namespace std;

int n, ans;

int main() {
    int i, a, cnt1 = 0; cin >> n;
    for (i = 0; i < n; i++) {
        cin >> a;
        if (a == 1) cnt1++;
        ans ^= a;
    }
    if (cnt1 == n) cout << (ans ? "cubelover" : "koosaga");
    else cout << (ans ? "koosaga" : "cubelover");
}
