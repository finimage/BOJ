#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll gcd(ll a, ll b) {
    while (b) {
        ll r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ll n, m; cin >> n >> m;
    cout << n / gcd(n, m) << "/" << m / gcd(n, m);
}
