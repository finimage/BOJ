#include<bits/stdc++.h>
using namespace std;

vector<int> prime, pri, ans, tmp;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, t, l, n, a; cin >> n;
    prime.resize(1000 * 3001, 1);
    ans.resize(n + 1);
    pri.push_back(1);
    for (i = 2; i <= 1000 * 3000; i++) {
        if (prime[i]) {
            if (i - pri.back() > 1001) pri.push_back(i);
            for (j = i * 2; j <= 1000 * 3000; j += i) prime[j] = 0;
        }
        if (pri.size() > 1000) break;
    }
    j = 0;
    for (i = 1; i <= n; i++) {
        if (ans[i]) continue;
        cout << "? " << i << ' ' << pri[j] << endl;
        cin >> a;
        if (a == i) ans[i] = i;
        else {
            tmp.push_back(a);
            t = 1;
            while (1) {
                cout << "? " << i << ' ' << pri[j] + t << endl;
                cin >> a;
                if (a == tmp[0]) break;
                tmp.push_back(a);
                t++;
            }
            l = tmp.size();
            for (t = 0; t < l; t++) ans[tmp[t]] = tmp[(t + 1) % l];
            tmp.clear();
        }
        j++;
    }
    cout << "! ";
    for (i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << endl;
}
