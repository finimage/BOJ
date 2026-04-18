#include<iostream>
#include<unordered_map>
#define ll long long
using namespace std;

struct info {
    ll arr[2][2];
};

unordered_map<int, info> um;

info m_m(info a, info b) {
    int i, j, t;
    info result = { 0, };
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (t = 0; t < 2; t++) {
                result.arr[i][j] += a.arr[i][t] * b.arr[t][j] % 1000;
                result.arr[i][j] %= 1000;
            }
        }
    }
    return result;
}

info res(int n) {
    info k, result;
    if (um.count(n)) return um[n];
    if (um.count(n / 2)) k = um[n / 2];
    else  k = res(n / 2);
    result = m_m(k, k);
    if (n % 2 == 1) return m_m(result, um[1]);
    return result;
}

string solve(int n) {
    if (n == 1) return "005";
    if (n == 2) return "027";
    info k = res(n - 1);
    ll ans = (28 * k.arr[1][0] + 6 * k.arr[1][1]) % 1000 - 1;
    while (ans <= 0) ans += 1000;
    string res = "";
    res += (char)(ans / 100 + '0');
    ans %= 100;
    res += (char)(ans / 10 + '0');
    ans %= 10;
    res += (char)(ans + '0');
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, T, n; cin >> T;
    um[1] = { { {6,-4},{1,0} } };
    for (i = 2; i < 2 * 1e9 + 1; i <<= 1) um[i] = m_m(um[i / 2], um[i / 2]);
    for (i = 1; i <= T; i++) {
        cin >> n;
        cout << "Case #" << i << ": " << solve(n) << '\n';
    }
}
