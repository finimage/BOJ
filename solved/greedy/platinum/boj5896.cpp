#include<iostream>
using namespace std;

int n, alp[26][1000001], ind[26];
char c;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, a, b, ans = 0, tmp, temp, tf; cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> c;
        alp[c - 'a'][ind[c - 'a']++] = i;
        alp[c - 'a'][ind[c - 'a']] = 1000001;
    }
    for (i = 0; i < 26; i++) {
        if (ind[i] == 0) continue;
        for (j = 0; j < 26; j++) {
            if (i == j || ind[j] == 0) continue;
            tmp = temp = 0;
            a = b = 0;
            tf = 0;
            while (a < ind[i]) {
                if (alp[i][a] < alp[j][b]) {
                    tmp++;
                    a++;
                }
                else {
                    tf = 1;
                    tmp--;
                    b++;
                }
                if (tmp < 0) {
                    tmp = 0;
                    tf = 0;
                }
                if (tf) temp = max(temp, tmp);
                else temp = max(temp, tmp - 1);
            }
            ans = max(ans, temp);
        }
    }
    cout << ans;
}
