#include<bits/stdc++.h>
#define ll long long
#define pli pair<ll, int>
#define a first
#define d second
using namespace std;

int n;
vector<pli> v;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i; cin >> n;
    v.resize(n);
    for (i = 0; i < n; i++) cin >> v[i].a >> v[i].d;
    sort(v.begin(), v.end());
    ll ri = 0, stop = 0, ans = 0;
    for (i = 0; i < n; i++) {
        if (v[i].d == -1) ans += stop * 2 + ri;
        if (v[i].d == 0) {
            ans += ri * 2;
            stop++;
        }
        if (v[i].d == 1) ri++;
    }
    cout << ans;
}
