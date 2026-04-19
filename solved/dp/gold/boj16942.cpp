#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

string s;
vector<int> odd[26], even[26];

void solve() {
    int i; cin >> s;
    for (i = 0; i < s.size(); i++) {
        if (i % 2) odd[s[i] - 'A'].push_back(i);
        else even[s[i] - 'A'].push_back(i);
    }
    int ans = 1;
    for (i = 0; i < 26; i++) {
        int i1 = 0, i2 = 0, tmp = 1;
        if (odd[i].size() == 0 || even[i].size() == 0) continue;
        if (odd[i][0] < even[i][0]) {
            i1 = 1;
            while (i1 < odd[i].size() && i2 < even[i].size()) {
                if (tmp % 2) {
                    while (i2 < even[i].size() && odd[i][i1 - 1] > even[i][i2]) i2++;
                    if (i2 == even[i].size()) break;
                    i2++;
                    tmp++;
                }
                else {
                    while (i1 < odd[i].size() && odd[i][i1] < even[i][i2 - 1]) i1++;
                    if (i1 == odd[i].size()) break;
                    i1++;
                    tmp++;
                }
            }
            if (tmp % 2) {
                while (i2 < even[i].size() && odd[i][i1 - 1] > even[i][i2]) i2++;
                if (i2 == even[i].size()) tmp--;
                i2++;
                tmp++;
            }
            else {
                while (i1 < odd[i].size() && odd[i][i1] < even[i][i2 - 1]) i1++;
                if (i1 == odd[i].size()) tmp--;
                i1++;
                tmp++;
            }
        }
        else {
            i2 = 1;
            while (i1 < odd[i].size() && i2 < even[i].size()) {
                if (tmp % 2 == 0) {
                    while (i2 < even[i].size() && odd[i][i1 - 1] > even[i][i2]) i2++;
                    if (i2 == even[i].size()) break;
                    i2++;
                    tmp++;
                }
                else {
                    while (i1 < odd[i].size() && odd[i][i1] < even[i][i2 - 1]) i1++;
                    if (i1 == odd[i].size()) break;
                    i1++;
                    tmp++;
                }
            }
            if (tmp % 2 == 0) {
                while (i2 < even[i].size() && odd[i][i1 - 1] > even[i][i2]) i2++;
                if (i2 == even[i].size()) tmp--;
                i2++;
                tmp++;
            }
            else {
                while (i1 < odd[i].size() && odd[i][i1] < even[i][i2 - 1]) i1++;
                if (i1 == odd[i].size()) tmp--;
                i1++;
                tmp++;
            }
        }
        ans = max(ans, tmp);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
