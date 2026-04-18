#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll n, m, q, contime[100001], ttime[100001];
unordered_set<int> small_contest[100001], large_contest;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int i, a, b, c; cin >> n >> m >> q;
    int sqrtn = 317;
    while (q--) {
        cin >> a >> b;
        if (a == 1) {
            cin >> c;
            if (small_contest[b].count(c)) {
                small_contest[b].erase(c);
                ttime[c] += contime[b];
                if (small_contest[b].size() == sqrtn) {
                    large_contest.erase(b);
                    if (contime[b]) {
                        for (auto& iter : small_contest[b]) ttime[iter] += contime[b];
                    }
                    contime[b] = 0;
                }
            }
            else {
                small_contest[b].insert(c);
                ttime[c] -= contime[b];
                if (small_contest[b].size() == sqrtn + 1) {
                    large_contest.insert(b);
                    if (contime[b]) {
                        for (auto& iter : small_contest[b]) ttime[iter] += contime[b];
                    }
                    contime[b] = 0;
                }
            }
        }
        else if (a == 2) {
            cin >> c;
            if (small_contest[b].size() > sqrtn) contime[b] += c;
            else {
                for (auto& iter : small_contest[b]) ttime[iter] += c;
            }
        }
        else {
            ll ans = ttime[b];
            for (auto& iter : large_contest) {
                if (small_contest[iter].count(b)) ans += contime[iter];
            }
            cout << ans << '\n';
        }
    }
}
