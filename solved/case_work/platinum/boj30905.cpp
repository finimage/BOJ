#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int cnt1, cnt2;
vector<ll> v;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, i; cin >> n;
    for (i = 0; i < n; i++) {
        ll a; cin >> a;
        if (a != 1 && a != 2) v.push_back(a);
        cnt1 += a == 1;
        cnt2 += a == 2;
    }
    sort(v.begin(), v.end());
    if (cnt1 == 0) {
        if (cnt2 == n) {
            cout << 2;
            for (i = 1; i < cnt2; i++) cout << "*2";
        }
        else {
            cout << v[0];
            for (i = 1; i < n - cnt2; i++) cout << "*" << v[i];
            for (i = 0; i < cnt2; i++) cout << "*2";
        }
    }
    else if (cnt1 <= cnt2) {
        cnt1--;
        cnt2--;
        cout << "(1+2)";
        for (i = 0; i < cnt1; i++) cout << "*(1+2)";
        cnt2 -= cnt1;
        for (i = 0; i < cnt2; i++) cout << "*2";
        for (auto& iter : v) cout << "*" << iter;
    }
    else if (cnt2 == 0) {
        if (cnt1 == 1) {
            if (n == 1) cout << 1;
            else {
                cout << "(1+";
                cout << v[0] << ")";
                for (i = 1; i < v.size(); i++) cout << "*" << v[i];
            }
        }
        else if (cnt1 == 2) {
            cout << "(1+1)";
            for (i = 0; i < v.size(); i++) cout << "*" << v[i];
        }
        else if (cnt1 % 3 == 0) {
            cout << "(1+1+1)";
            cnt1 -= 3;
            for (i = 0; i < cnt1 / 3; i++) cout << "*(1+1+1)";
            for (i = 0; i < v.size(); i++) cout << "*" << v[i];
        }
        else if (cnt1 % 3 == 1) {
            cout << "(1+1+1+1)";
            cnt1 -= 4;
            for (i = 0; i < cnt1 / 3; i++) cout << "*(1+1+1)";
            for (i = 0; i < v.size(); i++) cout << "*" << v[i];
        }
        else {
            cout << "(1+1)";
            cnt1 -= 2;
            for (i = 0; i < cnt1 / 3; i++) cout << "*(1+1+1)";
            for (i = 0; i < v.size(); i++) cout << "*" << v[i];
        }
    }
    else {
        if (cnt2 == 1 && cnt1 == 2) {
            cout << "(1+1+2)";
            cnt1--;
        }
        else cout << "(2+1)";
        cnt1--;
        cnt2--;
        if ((cnt1 - cnt2) % 3 == 1) {
            for (i = 1; i < cnt2; i++) {
                cout << "*(2+1)";
                cnt1--;
            }
            if (cnt2 == 0) {
                cnt1 -= 4;
                cout << "*(1+1+1+1)";
                for (i = 0; i < cnt1 / 3; i++) cout << "*(1+1+1)";
            }
            else {
                cout << "*(1+1+2)";
                cnt1 -= 2;
                for (i = 0; i < cnt1 / 3; i++) cout << "*(1+1+1)";
            }
        }
        else if ((cnt1 - cnt2) % 3 == 2) {
            for (i = 0; i < cnt2; i++) {
                cout << "*(2+1)";
                cnt1--;
            }
            cout << "*(1+1)";
            cnt1 -= 2;
            for (i = 0; i < cnt1 / 3; i++) cout << "*(1+1+1)";
        }
        else {
            for (i = 0; i < cnt2; i++) {
                cout << "*(2+1)";
                cnt1--;
            }
            for (i = 0; i < cnt1 / 3; i++) cout << "*(1+1+1)";
        }
        for (i = 0; i < v.size(); i++) cout << "*" << v[i];
    }
}
