#include<iostream>
using namespace std;

int n, check[1001], cnt;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, pre_le, pre_ri, le, ri; cin >> n;
    cout << "? 1 " << n << endl;
    cin >> pre_ri;
    cout << "? 1 " << n - 1 << endl;
    cin >> ri;
    if (ri == pre_ri - 1) {
        check[n] = 1;
        cnt++;
    }
    pre_le = 0;
    for (i = 1; i < n; i++) {
        cout << "? " << i + 1 << ' ' << n << endl;
        cin >> ri;
        cout << "? 1 " << i << endl;
        cin >> le;
        if (pre_le + 1 == le && pre_ri == ri + 1) {
			cnt++;
			check[i] = 1;
		}
        pre_le = le;
        pre_ri = ri;
    }
    cout << "! " << cnt << ' ';
    for (i = 1; i <= n; i++) {
        if (check[i]) cout << i << ' ';
    }
    cout << endl;
}
