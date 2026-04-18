#include<bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    long double a, b, h; cin >> a >> b >> h;
    if (a == b) cout << -1;
    else {
        if (a > b) swap(a, b);
        long double ans = (b + a) * ((b - a) * (b - a) + h * h) * 3.1415926535 / (b - a);
        printf("%Lf", ans);
    }
}
