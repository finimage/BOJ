#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

vector<pll> v;

ll ccw(pll a, pll b, pll c) {
    return a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll n, i, s = 0; cin >> n;
    v.resize(n);
    for (i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    for (i = 1; i < n - 1; i++) s += abs(ccw(v[0], v[i], v[i + 1]));
    ld ss = (ld)s / 2;
    cout << setprecision(15) << ss * (1 - (ld)3.141592653589793238462643383279 / 3 / sqrt(3)) / 3;
}
