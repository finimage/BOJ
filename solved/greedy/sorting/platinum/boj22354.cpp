#include<iostream>
#include<queue>
#define ll long long
using namespace std;

string S;
priority_queue<ll> pq;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, i, cnt = 1; cin >> N >> S;
    char pre = S[0]; ll temp, MAX = 0, ans = 0;
    for (i = 0; i < N; i++) {
        cin >> temp;
        if (pre != S[i]) {
            pre = S[i];
            if (cnt != 1) pq.push(MAX);
            MAX = 0;
            cnt++;
        }
        MAX = max(MAX, temp);
    }
    cnt = (cnt - 1) / 2;
    while (cnt--) {
        ans += pq.top();
        pq.pop();
    }
    cout << ans;
}
