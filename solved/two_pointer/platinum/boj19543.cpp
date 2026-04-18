#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n, m, k;
vector<int> v[26];
string s;

int bs1(int ind, int val) {
    if (v[ind].size() == 0) return -1;
    int le = 0, ri = v[ind].size() - 1, mid, res = -1;
    while (le <= ri) {
        mid = (le + ri) / 2;
        if (v[ind][mid] <= val) {
            res = v[ind][mid];
            le = mid + 1;
        }
        else ri = mid - 1;
    }
    return res;
}

int bs2(int ind, int val) {
    if (v[ind].size() == 0) return -1;
    int le = 0, ri = v[ind].size() - 1, mid, res = -1;
    while (le <= ri) {
        mid = (le + ri) / 2;
        if (v[ind][mid] < val) {
            res = v[ind][mid];
            le = mid + 1;
        }
        else ri = mid - 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j; cin >> n >> m >> k;
    for (i = 0; i < k; i++) {
        cin >> s;
        for (j = 0; j < m; j++) {
            if (s[j] == 'U') v[i].push_back(j);
        }
    }
    cin >> s;
    reverse(s.begin(), s.end());
    int le, ri = m - 1;
    if (v[s[0] - 'A'].size() == 0) le = 0;
    else if (v[s[0] - 'A'].size() == 1) {
        if (v[s[0] - 'A'][0] == m - 1) le = 0;
        else le = v[s[0] - 'A'][0] + 1;
    }
    else {
        if (v[s[0] - 'A'].back() == m - 1) le = v[s[0] - 'A'][v[s[0] - 'A'].size() - 2] + 1;
        else le = v[s[0] - 'A'].back() + 1;
    }
    ll ans = ri - le + 1;
    for (i = 1; i < n; i++) {
        int t = s[i] - 'A';
        int tmpri = bs1(t, ri);
        if (tmpri < le) break;
        int tmple = bs2(t, le) + 1;
        le = tmple;
        ri = tmpri;
        ans += ri - le + 1;
    }
    cout << ans;
}
