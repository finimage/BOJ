#include<iostream>
#include<vector>
using namespace std;

int n, p[1000001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, k = 0, K = 1000001, P = 1000001, cmp = 2000002; cin >> n;
    vector<string> v(n + 1);
    for (i = n; i > 0; i--) cin >> v[i];
    if (n == 1) {
        cout << "0 1";
        return 0;
    }
    for (i = 2; i <= n; i++) {
        while (k > 0 && v[k + 1] != v[i]) k = p[k];
        if (v[k + 1] == v[i]) k++;
        p[i] = k;
        if (p[i] <= p[i - 1]) {
            if (cmp > i - 1 - p[i - 1] + n - i + 1) {
                cmp = i - 1 - p[i - 1] + n - i + 1;
                P = i - 1 - p[i - 1];
                K = n - i + 1;
            }
            if (cmp == i - 1 - p[i - 1] + n - i + 1 && P > i - 1 - p[i - 1]) {
                P = i - 1 - p[i - 1];
                K = n - i + 1;
            }
        }
        else if (i == n) {
            if (cmp > i - 1 - p[i - 1]) {
                cmp = i - 1 - p[i - 1];
                P = i - 1 - p[i - 1];
                K = 0;
            }
            if (cmp == i - 1 - p[i - 1] && P > i - 1 - p[i - 1]) {
                P = i - 1 - p[i - 1];
                K = 0;
            }
        }
    }
    cout << K << ' ' << P;
}
